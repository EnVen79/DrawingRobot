#define RX 0
#define TX 1

SoftwareSerial Bluetooth(RX, TX);
const int maxLines = 10;
const int maxPoints = 20;

extern float coords[maxLines][maxPoints][2];
int lineCount = 0;

void GetCoord(String data) 
{
  int pointIndex = 0;
  lineCount = 0;

  int lineEndIndex = data.indexOf(' ');
  while (lineEndIndex != -1 || data.length() > 0) 
  {
    String line = (lineEndIndex != -1) ? data.substring(0, lineEndIndex) : data;
    data = (lineEndIndex != -1) ? data.substring(lineEndIndex + 1) : "";

    int coordEndIndex = line.indexOf(',');
    pointIndex = 0;

    while (coordEndIndex != -1 || line.length() > 0) 
    {
      String coord = (coordEndIndex != -1) ? line.substring(0, coordEndIndex) : line;
      line = (coordEndIndex != -1) ? line.substring(coordEndIndex + 1) : "";

      int dotIndex = coord.indexOf('.');
      if (dotIndex != -1 && pointIndex < maxPoints && lineCount < maxLines) 
      {
        coords[lineCount][pointIndex][0] = coord.substring(0, dotIndex).toInt();
        coords[lineCount][pointIndex][1] = coord.substring(dotIndex + 1).toInt();
        pointIndex++;
      }
      coordEndIndex = line.indexOf(',');
    }
    lineCount++;
    lineEndIndex = data.indexOf(' ');
  }
}