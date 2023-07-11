package org.sid.weatherapi.Entity;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.sql.Time;
import java.sql.Timestamp;

@Entity
@Data
@Table(name = "station1")
@NoArgsConstructor
@AllArgsConstructor
public class weatherStation {
    @Id
    @Column(name = "date")
    private Timestamp date;

    @Column(name = "hum_moy")
    private int hum_moy;
    @Column(name = "hum_min")
    private int hum_min;
    @Column(name = "hum_max")
    private int hum_max;

    @Column(name = "temp_moy")
    private float temp_moy;
    @Column(name = "temp_min")
    private float temp_min;
    @Column(name = "temp_max")
    private float temp_max;

    // Add a setter for the created_at field
    public void setCreated_at(Timestamp created_at) {
        this.date = created_at;
    }
}
