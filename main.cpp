#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>

using namespace std;

struct Point{
    int x;
    int y;
};

float distance(Point a, Point b);
float area(Point pArr[], int l);
float perimeter(Point pArr[], int l);
void writeFile (Point pArr[], float &per, float &area, int &l);
int readFile(Point pArr[], QString ReadFileName);

QString printQuad(Point Arr[4]);
QString printQuad(Point Arr[4])
{
    QString qsRetVal = "Quadrilateral with points: ";
    QString qsTemp;
    Point curPoint;
    for (int i=0; i<4; i++){
        qsTemp = "[%2;%3] ";
        curPoint = Arr[i];
        qsTemp=qsTemp.arg(curPoint.x).arg(curPoint.y);
        qsRetVal.append(qsTemp);
    }
    return qsRetVal;
}

int main()
{

    QString qsFileName = "points.txt";
    QString qsFileTest = "testPoints.txt";

    QFile resFile ("result.txt");
    resFile.remove();

    Point pArray[10];
    Point testArr[10];



    //readFile(pArray, qsFileName, qsFileName);
    //qDebug() << "debug message "<< endl << printQuad(pArray);
    int len = readFile(pArray, qsFileName);
    float a = area(pArray, len);
            float p = perimeter(pArray, len);
    writeFile(pArray, p, a, len);

    cout << "\n Test file: " << endl;

    //readFile(testArr, qsFileTest);
    //qDebug() << "debug message "<< endl << printQuad(testArr);
    int lenT = readFile(testArr, qsFileTest);
    float testP = perimeter(testArr, lenT);
    float testA = area(testArr, lenT);

            writeFile(testArr, testP, testA, lenT);
    //readFile(testArr, qsFileTest);

    return 0;
}


float distance(Point a, Point b){
    float dis = sqrt(pow((b.x-a.x), 2)+pow((b.y-a.y), 2));
    return dis;
}

float perimeter(Point pArr[], int l){
    float per = 0;
    int i = 0;
    if(l<3||l>10){
        cout<<"cannot calculate the perimeter"<<endl;
    }else {
        while(i<l-1){
            per = per + distance(pArr[i], pArr[i+1]);
            i++;
        }
        per = per + distance(pArr[i], pArr[0]);
        cout<<"The perimeter of the tetragon is " << per << ";" << endl;
        return per;
    }



}

float area(Point pArr[], int l){

    int i = 0;
    float area = 0;
    if(l<3||l>10){
        cout << "cannot calculate the area"<<endl;
    }else {
        while(i<l-1){
            area = area + (pArr[i].x*pArr[i+1].y-pArr[i+1].x*pArr[i].y);
            i++;
        }
        area = abs(0.5*(area + (pArr[i].x*pArr[0].y-pArr[0].x*pArr[i].y)));
        cout << "The total area of the tatragon is " << area << ";" << endl;
        return area;
    }



}

void writeFile (Point pArr[], float &per, float &area, int &l){
    QFile resFile ("result.txt");
    if(l<3||l>10){
        cout <<"nothing to write"<<endl;
    }else {
        if (resFile.open(QFile::WriteOnly |QFile::Append )){
            QTextStream out(&resFile);
            out<<"Points coordinates\r\n";
            for (int i=0; i<4; i++){
                out<<"Point "<< i+1 <<": ["<<pArr[i].x<<";"<<pArr[i].y<<"]\r\n";
            }
            out << "The perimeter of the tetragon is "<< per << ";\r\n";
            out << "The total area of the tetragon is " << area << ";\r\n";

            out<<"\r\n";
        }
    }


    }


int readFile(Point pArray[], QString readFile){
    QString message;
    QFile file(readFile);
    if (!file.exists()){
        message = "Can't find file %1 to read\n";
        message = message.arg(readFile);
        qDebug() << message;
        return -1;
    }

    if(!file.open(QFile::ReadOnly | QFile::Text))  {
        message = "Can't open the file %1 for reading\n";
        message = message.arg(readFile);
        qDebug() << message;
        return -1;
    }

    char buf[1024];
    int readCount;
    QString qsBuf;
    QStringList qslPoint;
    float X,Y;
    int i=0;
    int j = 0;
    while (!file.atEnd()){
        readCount = file.readLine(buf, sizeof(buf));
        j++;
    }
    cout<<"DEBUG ===> linecount "<<j<<endl;
    file.seek(0);

    if(j<3||j>10){
        cout<< "===> Nothing to read";

    }else {
        while (!file.atEnd()){
            readCount = file.readLine(buf, sizeof(buf));
            buf[readCount-1] = 0;
            qsBuf = buf;
            qslPoint = qsBuf.split(';');
            cout << buf << " readCount is " << readCount << endl;
            cout << " Y: " << qPrintable(qslPoint[1]) ;
            cout << " X: " << qPrintable(qslPoint[0])<< endl;
            X=qslPoint.at(0).toFloat();
            Y=qslPoint.at(1).toFloat();
            pArray[i].x=X;
            pArray[i].y=Y;

            i++;
        }}
    cout << "DEBUG RETURN " << i<<endl;

    return i;


}
