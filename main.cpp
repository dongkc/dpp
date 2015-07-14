#include <Poco/Util/ServerApplication.h>
#include <iostream>

#include "qpcpp.h"
#include "app.h"
#include "bsp.h"

#define MAX_QEVT_NUM 1000

using namespace std;
using namespace Poco;
using namespace Poco::Util;

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

  int main(const ArgVec& args)
  {
    static QP::QEvt const *io_queue[MAX_QEVT_NUM];
    static QP::QEvt const *process_queue[MAX_QEVT_NUM];
    static QP::QSubscrList subscrSto[MAX_QEVT_NUM];

    static QF_MPOOL_EL(FrameEvt) smlPoolSto[MAX_QEVT_NUM];


    QP::QF::init();  // initialize the framework and the underlying RT kernel

    BSP_init(); // initialize the BSP

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
