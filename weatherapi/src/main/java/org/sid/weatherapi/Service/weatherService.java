package org.sid.weatherapi.Service;

import org.sid.weatherapi.Entity.weatherStation;
import org.sid.weatherapi.Repository.weatherRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.sql.Time;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.List;

@Service
public class weatherService {

    @Autowired
    private weatherRepository weatherRepo;

    public weatherStation saveDetails(weatherStation ws){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");
        LocalDateTime localDateTime = LocalDateTime.now( ZoneOffset.of("+01:00")); // Add 1 hour to get GMT+1
        String formattedDateTime = localDateTime.format(formatter);
        ws.setCreated_at(Timestamp.valueOf(LocalDateTime.parse(formattedDateTime, formatter)));
        return weatherRepo.save(ws);
    }

    public List<weatherStation> getAllWeatherStations() {
        return weatherRepo.findAll();
    }

    public List<weatherStation> getWeatherStationsByDate(Timestamp date) {
        // Implement the logic to retrieve weather stations by date
        return weatherRepo.findByCreatedAt(date);
    }

    public List<weatherStation> getWeatherStationsByDateRange(Timestamp minDate, Timestamp maxDate) {
        // Implement the logic to retrieve weather stations within the date range
        return weatherRepo.findByCreatedAtBetween(minDate, maxDate);
    }
}
