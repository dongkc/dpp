#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <iostream>

#include "qpcpp.h"
#include "app.h"
#include "bsp.h"

#define MAX_QEVT_NUM 100000

using namespace std;
using namespace Poco;
using namespace Poco::Util;

string g_database_arg;
string g_data_path;

class SampleServer: public ServerApplication
{
public:
  SampleServer()
  {
  }

  ~SampleServer()
  {
  }

protected:
  void initialize(Application& self)
  {
    loadConfiguration();
    ServerApplication::initialize(self);
  }

  void uninitialize()
  {
    ServerApplication::uninitialize();
  }

  void printProperties(const std::string& base)
  {
    AbstractConfiguration::Keys keys;
    config().keys(base, keys);
    if (keys.empty()) {
      if (config().hasProperty(base)) {
        std::string msg;
        msg.append(base);
        msg.append(" = ");
        msg.append(config().getString(base));
        LOG(INFO) << msg;
      }
    } else {
      for (auto& key: keys) {
        std::string fullKey = base;
        if (!fullKey.empty()) {
          fullKey += '.';
        }
        fullKey.append(key);
        printProperties(fullKey);
      }
    }
  }

  int main(const ArgVec& args)
  {
    printProperties("");
    g_database_arg = config().getString("database", "");
    g_data_path = config().getString("raw_data_path", "");

    return runnning();
  }

  int runnning()
  {
    static QP::QEvt const *io_queue[MAX_QEVT_NUM];
    static QP::QEvt const *process_queue[MAX_QEVT_NUM];
    static QP::QSubscrList subscrSto[MAX_QEVT_NUM];

    static QF_MPOOL_EL(FrameEvts) smlPoolSto[MAX_QEVT_NUM];

    QP::QF::init();

    BSP_init();

    QS_OBJ_DICTIONARY(smlPoolSto);
    QS_OBJ_DICTIONARY(io_queue);
    QS_OBJ_DICTIONARY(process_queue);

    QP::QF::psInit(subscrSto, Q_DIM(subscrSto)); // init publish-subscribe

    QP::QF::poolInit(smlPoolSto,
                     sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

    AO_iomgr->start(0,
                      process_queue, Q_DIM(process_queue),
                      (void *)0, 0U);
    AO_database->start(1,
                    io_queue, Q_DIM(io_queue),
                    (void *)0, 0U);

    return QP::QF::run();
  }

private:
};

POCO_SERVER_MAIN(SampleServer)
