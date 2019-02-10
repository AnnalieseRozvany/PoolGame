#include <QApplication>

#include "dialog.h"
#include "initializer.h"
#include "poolgame.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    std::string configFilePath = "/Users/annalieserozvany/INFO3220/Poolgame/config.json";
    PoolGame* game = Initializer().createPoolgame(configFilePath,&w);
    QFile conf_file("/Users/annalieserozvany/INFO3220/Poolgame/config.json");
    conf_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = conf_file.readAll();
    conf_file.close();
    QJsonObject config = QJsonDocument::fromJson(content.toUtf8()).object();
    if (config.value("stage3").toBool()) {
        w.stage3();
    }
    //if the returned game is a nullptr the json file couldn't be found or was invalid
    if(!game) return a.exec();
    w.show();
    w.start(game);

    return a.exec();

}
