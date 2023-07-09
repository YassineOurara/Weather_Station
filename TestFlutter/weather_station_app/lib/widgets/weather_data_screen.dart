import 'package:flutter/material.dart';
import 'package:fl_chart/fl_chart.dart';
import '/service/data_service.dart';
import 'package:intl/intl.dart';

class WeatherDataScreen extends StatefulWidget {
  @override
  _WeatherDataScreenState createState() => _WeatherDataScreenState();
}

class _WeatherDataScreenState extends State<WeatherDataScreen> {
  List<Map<String, dynamic>> weatherList = [];
  DateTime minDate = DateTime.now();
  DateTime maxDate = DateTime.now();

  @override
  void initState() {
    super.initState();
    fetchData();
  }

  Future<void> fetchData() async {
    final dataService = DataService();
    weatherList = await dataService.getData();
    setState(() {}); // Trigger a rebuild after data is fetched
  }

  void updateMinDate(DateTime newMinDate) {
    setState(() {
      minDate = newMinDate;
    });
  }

  void updateMaxDate(DateTime newMaxDate) {
    setState(() {
      maxDate = newMaxDate;
    });
  }

  void onFilterButtonPressed() {
    // Perform filtering based on minDate and maxDate
    // You can add your custom logic here
    print('Filter button pressed!');
    print('Min Date: $minDate');
    print('Max Date: $maxDate');
  }

@override
Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(
      title: Text('Weather Data'),
    ),
    body: SingleChildScrollView(
      child: Center(
        child: Column(
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Container(
                  padding: EdgeInsets.all(16.0),
                  child: Row(
                    children: [
                      Text('Min Date:'),
                      SizedBox(width: 10.0),
                      GestureDetector(
                        onTap: () {
                          showDatePicker(
                            context: context,
                            initialDate: minDate,
                            firstDate: DateTime(2000),
                            lastDate: maxDate,
                          ).then((selectedDate) {
                            if (selectedDate != null) {
                              updateMinDate(selectedDate);
                            }
                          });
                        },
                        child: Text(
                          '${DateFormat('dd/MM/yyyy').format(minDate)}',
                          style: TextStyle(
                            decoration: TextDecoration.underline,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                      SizedBox(width: 10.0),
                      GestureDetector(
                        onTap: () {
                          showTimePicker(
                            context: context,
                            initialTime: TimeOfDay.fromDateTime(minDate),
                          ).then((selectedTime) {
                            if (selectedTime != null) {
                              final newMinDate = DateTime(
                                minDate.year,
                                minDate.month,
                                minDate.day,
                                selectedTime.hour,
                                selectedTime.minute,
                              );
                              updateMinDate(newMinDate);
                            }
                          });
                        },
                        child: Text(
                          '${DateFormat('HH:mm').format(minDate)}',
                          style: TextStyle(
                            decoration: TextDecoration.underline,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                    ],
                  ),
                ),
                Container(
                  padding: EdgeInsets.all(16.0),
                  child: Row(
                    children: [
                      Text('Max Date:'),
                      SizedBox(width: 10.0),
                      GestureDetector(
                        onTap: () {
                          showDatePicker(
                            context: context,
                            initialDate: maxDate,
                            firstDate: minDate,
                            lastDate: DateTime(2100),
                          ).then((selectedDate) {
                            if (selectedDate != null) {
                              updateMaxDate(selectedDate);
                            }
                          });
                        },
                        child: Text(
                          '${DateFormat('dd/MM/yyyy').format(maxDate)}',
                          style: TextStyle(
                            decoration: TextDecoration.underline,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                      SizedBox(width: 10.0),
                      GestureDetector(
                        onTap: () {
                          showTimePicker(
                            context: context,
                            initialTime: TimeOfDay.fromDateTime(maxDate),
                          ).then((selectedTime) {
                            if (selectedTime != null) {
                              final newMaxDate = DateTime(
                                maxDate.year,
                                maxDate.month,
                                maxDate.day,
                                selectedTime.hour,
                                selectedTime.minute,
                              );
                              updateMaxDate(newMaxDate);
                            }
                          });
                        },
                        child: Text(
                          '${DateFormat('HH:mm').format(maxDate)}',
                          style: TextStyle(
                            decoration: TextDecoration.underline,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                    ],
                  ),
                ),
                SizedBox(width: 10.0),
                ElevatedButton(
                  onPressed: onFilterButtonPressed,
                  child: Text('Rafraîchir'),
                ),
              ],
            ),
            SizedBox(height: 16.0),
            weatherList.isEmpty
                ? CircularProgressIndicator()
                : Row(
              children: [
                Expanded(
                  child: Container(
                    height: 450.0, // Adjust the height as needed
                    child: Card(
                      color: Colors.grey[200], // Light gray background color
                      child: Column(
                        children: [
                          Container(
                            padding: EdgeInsets.all(8.0),
                            child: Text(
                              'Données de la station',
                              style: TextStyle(
                                fontWeight: FontWeight.bold,
                                fontSize: 16.0,
                              ),
                            ),
                          ),
                          Divider(
                            color: Colors.black,
                            thickness: 1.0,
                          ),
                          Expanded(
                            child: SingleChildScrollView(
                              scrollDirection: Axis.vertical,
                              child: SingleChildScrollView(
                                scrollDirection: Axis.horizontal,
                                child: DataTable(
                                  columnSpacing: 6.0, // Adjust the column spacing as needed
                                  horizontalMargin: 6.0,
                                  columns: weatherList.isEmpty
                                      ? []
                                      : [
                                    for (var data in weatherList)
                                      DataColumn(
                                        label: Container(
                                          padding: EdgeInsets.symmetric(vertical: 8.0),
                                          child: Column(
                                            children: [
                                              Center(
                                                child: Text(
                                                  data['name'],
                                                  textAlign: TextAlign.center,
                                                  style: TextStyle(
                                                    fontWeight: FontWeight.bold,
                                                  ),
                                                ),
                                              ),
                                              Divider(
                                                color: Colors.black,
                                                thickness: 1.0,
                                              ),
                                            ],
                                          ),
                                        ),
                                      ),
                                  ],
                                  rows: weatherList.isEmpty
                                      ? []
                                      : List.generate(
                                    weatherList[0]['values'].length,
                                        (index) => DataRow(
                                      cells: [
                                        for (var data in weatherList)
                                          DataCell(
                                            Container(
                                              padding: EdgeInsets.all(8.0),
                                              child: Center(
                                                child: Text(
                                                  data['values'][index].toString(),
                                                ),
                                              ),
                                            ),
                                          ),
                                      ],
                                    ),
                                  ),
                                ),
                              ),
                            ),
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
                Expanded(
                  child: Container(
                    height: 450.0, // Adjust the height as needed
                    child: Card(
                      color: Colors.grey[200], // Light gray background color
                      child: Column(
                        children: [
                          Container(
                            padding: EdgeInsets.all(8.0),
                            child: Text(
                              'Température [°C]',
                              style: TextStyle(
                                fontWeight: FontWeight.bold,
                                fontSize: 16.0,
                              ),
                            ),
                          ),
                          Divider(
                            color: Colors.black,
                            thickness: 1.0,
                          ),
                          Expanded(
                            child: Container(
                              padding: EdgeInsets.all(16.0),
                              child: LineChart(
                                LineChartData(
                                  minX: 0,
                                  maxX: weatherList[0]['values'].length.toDouble() - 1,
                                  minY: weatherList[1]['values'].reduce((min, value) => min < value ? min : value),
                                  maxY: weatherList[1]['values'].reduce((max, value) => max > value ? max : value),
                                  titlesData: FlTitlesData(
                                    show: true,
                                    bottomTitles: SideTitles(
                                      showTitles: true,
                                      reservedSize: 80, // Adjust the reserved size as needed
                                      getTextStyles: (context, value) => const TextStyle(
                                        color: Color(0xff72719c),
                                        fontSize: 10,
                                      ),
                                      getTitles: (value) {
                                        if (value.toInt() >= 0 && value.toInt() < weatherList[0]['values'].length) {
                                          return weatherList[0]['values'][value.toInt()];
                                        }
                                        return '';
                                      },
                                      margin: 8,
                                      rotateAngle: -80,
                                    ),
                                    leftTitles: SideTitles(
                                      showTitles: true,
                                      getTextStyles: (context, value) => const TextStyle(
                                        color: Color(0xff75729e),
                                        fontSize: 14,
                                      ),
                                      getTitles: (value) {
                                        return value.toInt().toString();
                                      },
                                      margin: 8,
                                    ),
                                  ),
                                  borderData: FlBorderData(
                                    show: true,
                                    border: Border.all(color: const Color(0xff37434d), width: 1),
                                  ),
                                  lineBarsData: [
                                    LineChartBarData(
                                      spots: List.generate(
                                        weatherList[0]['values'].length,
                                        (index) => FlSpot(
                                          index.toDouble(),
                                          weatherList[1]['values'][index].toDouble(),
                                        ),
                                      ),
                                      isCurved: true,
                                      colors: const [Color(0xff23b6e6)],
                                      barWidth: 4,
                                      isStrokeCapRound: true,
                                      dotData: FlDotData(show: true),
                                      belowBarData: BarAreaData(show: false),
                                    ),
                                  ],
                                ),
                              ),
                            ),
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    ),
  );
}

}