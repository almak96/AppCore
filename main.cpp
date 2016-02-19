#include <iostream>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QDate>
#include <QtSql/QSql>

using namespace std;

//Переменные

const int sizeDay = 2;
int version = 1;
QString fileString;
struct dayStruct
{

    bool chetnost;
    int numberDay;
    QVector<QString> classes;
    QVector<QString> numberClass;



    //bool notNormal;
    //QString notNormalString;
} day[sizeDay];


//Функции

void intVersion(); //Проверка новой версии и запись в стоку
void convertString(); //Конвертирование строки в структуру
int getToday();//Возваращает расписание на данный день
int getTomorrow();//Возваращает расписание на завтрашний день
int getNextTomorrow();//Возваращает расписание на послезавтра
int getTypeofWeek(); //Возрващает 1-нечетная 0-четная




//Описание функций

void initVersion()
{
    QString nextVersionNumber;
    QString currentVersion;
    QString txt = ".txt";


    int nextVersion = version+1;
    nextVersionNumber = QString::number(nextVersion);
    currentVersion = QString::number(version);
    nextVersionNumber.append(txt);
    currentVersion.append(txt);

    QFile dataFile(nextVersionNumber);
    if(!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QFile dataFile(currentVersion);
    }
    else
    {
        version +=1;
    }

    QTextStream in(&dataFile);
    fileString = in.readAll();

}



void convertString()
{
    //int interval;
    int dayN = 0;
   while(dayN<sizeDay) {
        for(int i = 0; i<fileString.size();i++)
        {
            switch (fileString.at(i).toLatin1())
            {
                case '|':
                    day[dayN].chetnost = true;
                break;


                case '_':
                    day[dayN].chetnost = false;
                 break;

                case '^':{

                    QString buff;
                    bool ok = false;
                    buff = fileString.at(i+1);
                    day[dayN].numberDay = buff.toInt(&ok, 10);
                    i++;
                    break;
                    }


            case '&':{
                i++;
                QString buff;
                    while(fileString.at(i).toLatin1()!=35)//56 90  97 112
                    {

                        buff.append(fileString.at(i));
                        //interval++;
                        if(fileString.at(i+1).toLatin1()==35)
                        {
                            day[dayN].numberClass.append(fileString.at(i+2));
                            day[dayN].classes.append(buff);

                        }
                        i++;
                    }

                    i++;
                break;
                    }
                case ';':
                        dayN++;
                break;
            default:
                //interval = 5;
                break;




         }
        }
    }

}



int getTypeofWeek()
{
    QDate today;
    today = today.currentDate();
    int currentYear = today.year();
    int *p= &currentYear;
    int week = today.weekNumber();



    return ;

}


\

int main()
{
 //initVersion();

getTypeofWeek();
 //convertString();


    return 0;
}
