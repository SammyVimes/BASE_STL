#include <iostream>
#include <fstream>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QCryptographicHash>

#include "HashMap.h"

using namespace std;
using namespace containers;
#define final const

int main() {
    HashMap<QString, int>* map = new HashMap<QString, int>();
    QString str("10");
    map->put(str, 10);
    str = QString("11");
    map->put(str, 11);
    return 0;
}
