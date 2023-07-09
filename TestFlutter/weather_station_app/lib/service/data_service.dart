import 'package:intl/intl.dart';
import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:crypto/crypto.dart';

class DataService {
    Future<List<Map<String, dynamic>>> getData() async {
    String givenDateMin = "26/07/2022 10:00:00";
    String givenDateMax = "27/07/2022 11:00:06";
    String station = "00206458";
    String type = "hours";
    DateTime formattedDateMin =
        DateFormat("dd/MM/yyyy HH:mm:ss").parse(givenDateMin);
    DateTime formattedDateMax =
        DateFormat("dd/MM/yyyy HH:mm:ss").parse(givenDateMax);
    int unixTimestampMin = formattedDateMin.millisecondsSinceEpoch ~/ 1000;
    int unixTimestampMax = formattedDateMax.millisecondsSinceEpoch ~/ 1000;

    String apiRoute =
        '/data/$station/$type/from/$unixTimestampMin/to/$unixTimestampMax';
    String publicKey = "632fef96a6e94fc62dfc70b3d31bdac8f492dc5e5a71df78";
    String privateKey = "245b514ca34836323756f1ed7c401263a7dbd93ae199f46d";
    String apiURI = "https://api.fieldclimate.com/v2";

    String contentToSign = 'GET$apiRoute$publicKey';
    var key = utf8.encode(privateKey);
    var bytesG = utf8.encode(contentToSign);
    var hmacSha256 = Hmac(sha256, key);
    var digest = hmacSha256.convert(bytesG);
    var signature = digest.toString();

    String authorizationString = "hmac $publicKey:$signature";

    try {
      final response = await http.get(Uri.parse(apiURI + apiRoute), headers: {
        'Content-Type': 'application/json',
        'Authorization': authorizationString,
      });

      final json = jsonDecode(response.body);
      List<dynamic> data = json['data'];
      List<Map<String, dynamic>> output = [];

      for (var item in data) {
        String name = item['name'];
        if (item['aggr'] != null) {
          List<dynamic> aggr = item['aggr'];

          for (var aggrString in aggr) {
            String newName = name + ' ' + aggrString.toString();
            List<dynamic> values = item['values'][aggrString];

            Map<String, dynamic> result = {
              'name': newName,
              'values': values,
            };

            output.add(result);
          }
        } else {
          List<dynamic> values = item['values']['result'];
          Map<String, dynamic> result = {
            'name': name,
            'values': values,
          };

          output.add(result);
        }
      }

      print(output);
      return output;
    } catch (error) {
      print("An error occurred: $error");
      return [];
    }
  }
}