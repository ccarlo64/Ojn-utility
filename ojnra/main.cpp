#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDataStream>
#include <QCryptographicHash>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "****************************************";
    qDebug() << "* Read Openjabnab account file utility *";
    qDebug() << "****************************************";

    bool newAccount = false;
    QString nFile="";
    if (argc==2) {
      if (!strcmp(argv[1],"new")) {
        newAccount=true;
      } else {
        nFile= argv[1];
      }
    } else {
      qDebug() << endl << "use:" << argv[0] << " filename" << endl;
      qDebug() << "if filename is 'new' will create a file account";
      qDebug() << "sysadm.dat user:sysadm password:sysadm";
      qDebug() << "no filename specified" << endl;
      return 0;
    }

    enum Right { None = 0x0, Read = 0x1, Write = 0x2, ReadWrite = 0x3};
    enum Access { AcGlobal = 0x0, AcAccount = 0x1, AcBunnies = 0x2, AcZtamps = 0x3, AcPluginsBunny = 0x4, AcPluginsZtamp = 0x5, AcPlugins= 0x6, AcServer = 0x7};

    QString login;
    QString username;
    QByteArray passwordHash;
    bool isAdmin;
    QList<int> UserAccess;
    QList<QByteArray> listOfBunnies;
    QList<QByteArray> listOfZtamps;
    int ver;
    ver = 1;
    login = "sysadm";
    username = "sysadm";
    passwordHash = QCryptographicHash::hash("sysadm", QCryptographicHash::Md5);
    isAdmin = true;
    UserAccess << Read;
    UserAccess << ReadWrite;
    UserAccess << ReadWrite;
    UserAccess << ReadWrite;
    UserAccess << ReadWrite;
    UserAccess << ReadWrite;
    UserAccess << Read;
    UserAccess << None;
/*QList<int>::iterator i;
for (i = UserAccess.begin(); i != UserAccess.end(); ++i)
qDebug() << "." << *i;
*/
    if (newAccount) {
      QFile filehandleOUT( "sysadm.dat" );
      filehandleOUT.open(QIODevice::WriteOnly);
      QDataStream out(&filehandleOUT);
      out << ver << login << username << passwordHash << isAdmin ;
      out << UserAccess; 
      out << listOfBunnies << listOfZtamps;
      filehandleOUT.close();
      qDebug() << "file sysadm.dat created" << endl;
      return 0;
    }

    QFile filehandle( nFile);
    filehandle.open(QIODevice::ReadOnly);
    QDataStream in(&filehandle);
    in >> ver >> login >> username >> passwordHash >> isAdmin >> UserAccess >> listOfBunnies >> listOfZtamps;

    qDebug() << "version: " << ver;
    qDebug() << "login   : " <<login;
    qDebug() << "username: " <<username;// <<endl;

    if (isAdmin) {
        qDebug() << "is a Admin!";
    } else {
        qDebug() << "not is a Admin!";
    }
    qDebug() << "***** user access *****";
    /*int z;
    for(int i=0;i<8;i++) {
        UserAccess >> z;
        qDebug() << " " << z;
    }*/

    qDebug() << "       AcGlobal: " <<UserAccess[AcGlobal] << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";
    qDebug() << "      AcAccount: " <<UserAccess[AcAccount]  << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";
    qDebug() << "      AcBunnies: " <<UserAccess[AcBunnies]  << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";
    qDebug() << "       AcZtamps: " <<UserAccess[AcZtamps]  << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";
    qDebug() << " AcPluginsBunny: " <<UserAccess[AcPluginsBunny]  << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";
    qDebug() << " AcPluginsZtamp: " <<UserAccess[AcPluginsZtamp]  << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";
    qDebug() << "      AcPlugins: " <<UserAccess[AcPlugins]  << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";
    qDebug() << "       AcServer: " <<UserAccess[AcServer]  << " (0)None, (1)Read, (2)Write, (3)ReadWrite ";

    qDebug() << "list Of Bunnies: " << listOfBunnies;
    qDebug() << "list Of Ztamps : " << listOfZtamps;

    filehandle.close();

    return 0;
    //return a.exec();
}
