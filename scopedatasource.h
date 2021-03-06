#include <QObject>

#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <netlink/msg.h>
#include <netlink/attr.h>

class Ad9520;
class Adc08d1020;
class Dac101c085;
class Lmh6518;

class ScopeDataSource : public QObject
{
    Q_OBJECT

public:
    ScopeDataSource(QObject *parent = NULL);
    ~ScopeDataSource(void);

    int frequency() const;
    int amplitude() const;

public slots:
    void setAmplitude(int);
    void setFrequency(int);
    void setDacOffset(int);
    void setDacTrigger(int);
    void setAfeFilter(int);
    void setAfeAttenuation(int);
    int getData(int samples);

protected:

private:
    bool openDevice(void);
    struct nl_msg *allocMsg(int cmd);
    int sendReadRequest(void);
    int doReadRequest(void);

    struct nl_sock *handle;
    struct nl_cache *cache;
    struct genl_family *id;
    nlmsghdr *nhdr;
    void *bufferData;
    quint8 *bufferDataPtr;
    int bufferDataSize;

    int d_frequency;
    int d_amplitude;
    Ad9520 *pll;
    Adc08d1020 *adc;
    Dac101c085 *dac;
    Lmh6518 *vga;

signals:
    void scopeData(const QByteArray channel1, const QByteArray channel2);
};
