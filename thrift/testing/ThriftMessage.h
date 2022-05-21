/**
 * Autogenerated by Thrift Compiler (0.15.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ThriftMessage_H
#define ThriftMessage_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "testing_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class ThriftMessageIf {
 public:
  virtual ~ThriftMessageIf() {}
  virtual int32_t sendInt(const IntMessage& intMsg) = 0;
  virtual void sendStr(std::string& _return, const StringMessage& strMsg) = 0;
  virtual double sendDouble(const DoubleMessage& doubleMsg) = 0;
  virtual void sendShortMsg(ShortMessage& _return, const ShortMessage& srtMsg) = 0;
  virtual void sendLargeMsg(LargeMessage& _return, const LargeMessage& lrgMsg) = 0;
  virtual void ping() = 0;
};

class ThriftMessageIfFactory {
 public:
  typedef ThriftMessageIf Handler;

  virtual ~ThriftMessageIfFactory() {}

  virtual ThriftMessageIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(ThriftMessageIf* /* handler */) = 0;
  };

class ThriftMessageIfSingletonFactory : virtual public ThriftMessageIfFactory {
 public:
  ThriftMessageIfSingletonFactory(const ::std::shared_ptr<ThriftMessageIf>& iface) : iface_(iface) {}
  virtual ~ThriftMessageIfSingletonFactory() {}

  virtual ThriftMessageIf* getHandler(const ::apache::thrift::TConnectionInfo&) override {
    return iface_.get();
  }
  virtual void releaseHandler(ThriftMessageIf* /* handler */) override {}

 protected:
  ::std::shared_ptr<ThriftMessageIf> iface_;
};

class ThriftMessageNull : virtual public ThriftMessageIf {
 public:
  virtual ~ThriftMessageNull() {}
  int32_t sendInt(const IntMessage& /* intMsg */) override {
    int32_t _return = 0;
    return _return;
  }
  void sendStr(std::string& /* _return */, const StringMessage& /* strMsg */) override {
    return;
  }
  double sendDouble(const DoubleMessage& /* doubleMsg */) override {
    double _return = 0.0;
    return _return;
  }
  void sendShortMsg(ShortMessage& /* _return */, const ShortMessage& /* srtMsg */) override {
    return;
  }
  void sendLargeMsg(LargeMessage& /* _return */, const LargeMessage& /* lrgMsg */) override {
    return;
  }
  void ping() override {
    return;
  }
};

typedef struct _ThriftMessage_sendInt_args__isset {
  _ThriftMessage_sendInt_args__isset() : intMsg(false) {}
  bool intMsg :1;
} _ThriftMessage_sendInt_args__isset;

class ThriftMessage_sendInt_args {
 public:

  ThriftMessage_sendInt_args(const ThriftMessage_sendInt_args&) noexcept;
  ThriftMessage_sendInt_args& operator=(const ThriftMessage_sendInt_args&) noexcept;
  ThriftMessage_sendInt_args() noexcept {
  }

  virtual ~ThriftMessage_sendInt_args() noexcept;
  IntMessage intMsg;

  _ThriftMessage_sendInt_args__isset __isset;

  void __set_intMsg(const IntMessage& val);

  bool operator == (const ThriftMessage_sendInt_args & rhs) const
  {
    if (!(intMsg == rhs.intMsg))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendInt_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendInt_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_sendInt_pargs {
 public:


  virtual ~ThriftMessage_sendInt_pargs() noexcept;
  const IntMessage* intMsg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendInt_result__isset {
  _ThriftMessage_sendInt_result__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendInt_result__isset;

class ThriftMessage_sendInt_result {
 public:

  ThriftMessage_sendInt_result(const ThriftMessage_sendInt_result&) noexcept;
  ThriftMessage_sendInt_result& operator=(const ThriftMessage_sendInt_result&) noexcept;
  ThriftMessage_sendInt_result() noexcept
                               : success(0) {
  }

  virtual ~ThriftMessage_sendInt_result() noexcept;
  int32_t success;

  _ThriftMessage_sendInt_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const ThriftMessage_sendInt_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendInt_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendInt_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendInt_presult__isset {
  _ThriftMessage_sendInt_presult__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendInt_presult__isset;

class ThriftMessage_sendInt_presult {
 public:


  virtual ~ThriftMessage_sendInt_presult() noexcept;
  int32_t* success;

  _ThriftMessage_sendInt_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _ThriftMessage_sendStr_args__isset {
  _ThriftMessage_sendStr_args__isset() : strMsg(false) {}
  bool strMsg :1;
} _ThriftMessage_sendStr_args__isset;

class ThriftMessage_sendStr_args {
 public:

  ThriftMessage_sendStr_args(const ThriftMessage_sendStr_args&);
  ThriftMessage_sendStr_args& operator=(const ThriftMessage_sendStr_args&);
  ThriftMessage_sendStr_args() noexcept {
  }

  virtual ~ThriftMessage_sendStr_args() noexcept;
  StringMessage strMsg;

  _ThriftMessage_sendStr_args__isset __isset;

  void __set_strMsg(const StringMessage& val);

  bool operator == (const ThriftMessage_sendStr_args & rhs) const
  {
    if (!(strMsg == rhs.strMsg))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendStr_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendStr_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_sendStr_pargs {
 public:


  virtual ~ThriftMessage_sendStr_pargs() noexcept;
  const StringMessage* strMsg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendStr_result__isset {
  _ThriftMessage_sendStr_result__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendStr_result__isset;

class ThriftMessage_sendStr_result {
 public:

  ThriftMessage_sendStr_result(const ThriftMessage_sendStr_result&);
  ThriftMessage_sendStr_result& operator=(const ThriftMessage_sendStr_result&);
  ThriftMessage_sendStr_result() noexcept
                               : success() {
  }

  virtual ~ThriftMessage_sendStr_result() noexcept;
  std::string success;

  _ThriftMessage_sendStr_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const ThriftMessage_sendStr_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendStr_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendStr_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendStr_presult__isset {
  _ThriftMessage_sendStr_presult__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendStr_presult__isset;

class ThriftMessage_sendStr_presult {
 public:


  virtual ~ThriftMessage_sendStr_presult() noexcept;
  std::string* success;

  _ThriftMessage_sendStr_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _ThriftMessage_sendDouble_args__isset {
  _ThriftMessage_sendDouble_args__isset() : doubleMsg(false) {}
  bool doubleMsg :1;
} _ThriftMessage_sendDouble_args__isset;

class ThriftMessage_sendDouble_args {
 public:

  ThriftMessage_sendDouble_args(const ThriftMessage_sendDouble_args&) noexcept;
  ThriftMessage_sendDouble_args& operator=(const ThriftMessage_sendDouble_args&) noexcept;
  ThriftMessage_sendDouble_args() noexcept {
  }

  virtual ~ThriftMessage_sendDouble_args() noexcept;
  DoubleMessage doubleMsg;

  _ThriftMessage_sendDouble_args__isset __isset;

  void __set_doubleMsg(const DoubleMessage& val);

  bool operator == (const ThriftMessage_sendDouble_args & rhs) const
  {
    if (!(doubleMsg == rhs.doubleMsg))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendDouble_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendDouble_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_sendDouble_pargs {
 public:


  virtual ~ThriftMessage_sendDouble_pargs() noexcept;
  const DoubleMessage* doubleMsg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendDouble_result__isset {
  _ThriftMessage_sendDouble_result__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendDouble_result__isset;

class ThriftMessage_sendDouble_result {
 public:

  ThriftMessage_sendDouble_result(const ThriftMessage_sendDouble_result&) noexcept;
  ThriftMessage_sendDouble_result& operator=(const ThriftMessage_sendDouble_result&) noexcept;
  ThriftMessage_sendDouble_result() noexcept
                                  : success(0) {
  }

  virtual ~ThriftMessage_sendDouble_result() noexcept;
  double success;

  _ThriftMessage_sendDouble_result__isset __isset;

  void __set_success(const double val);

  bool operator == (const ThriftMessage_sendDouble_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendDouble_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendDouble_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendDouble_presult__isset {
  _ThriftMessage_sendDouble_presult__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendDouble_presult__isset;

class ThriftMessage_sendDouble_presult {
 public:


  virtual ~ThriftMessage_sendDouble_presult() noexcept;
  double* success;

  _ThriftMessage_sendDouble_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _ThriftMessage_sendShortMsg_args__isset {
  _ThriftMessage_sendShortMsg_args__isset() : srtMsg(false) {}
  bool srtMsg :1;
} _ThriftMessage_sendShortMsg_args__isset;

class ThriftMessage_sendShortMsg_args {
 public:

  ThriftMessage_sendShortMsg_args(const ThriftMessage_sendShortMsg_args&);
  ThriftMessage_sendShortMsg_args& operator=(const ThriftMessage_sendShortMsg_args&);
  ThriftMessage_sendShortMsg_args() noexcept {
  }

  virtual ~ThriftMessage_sendShortMsg_args() noexcept;
  ShortMessage srtMsg;

  _ThriftMessage_sendShortMsg_args__isset __isset;

  void __set_srtMsg(const ShortMessage& val);

  bool operator == (const ThriftMessage_sendShortMsg_args & rhs) const
  {
    if (!(srtMsg == rhs.srtMsg))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendShortMsg_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendShortMsg_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_sendShortMsg_pargs {
 public:


  virtual ~ThriftMessage_sendShortMsg_pargs() noexcept;
  const ShortMessage* srtMsg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendShortMsg_result__isset {
  _ThriftMessage_sendShortMsg_result__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendShortMsg_result__isset;

class ThriftMessage_sendShortMsg_result {
 public:

  ThriftMessage_sendShortMsg_result(const ThriftMessage_sendShortMsg_result&);
  ThriftMessage_sendShortMsg_result& operator=(const ThriftMessage_sendShortMsg_result&);
  ThriftMessage_sendShortMsg_result() noexcept {
  }

  virtual ~ThriftMessage_sendShortMsg_result() noexcept;
  ShortMessage success;

  _ThriftMessage_sendShortMsg_result__isset __isset;

  void __set_success(const ShortMessage& val);

  bool operator == (const ThriftMessage_sendShortMsg_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendShortMsg_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendShortMsg_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendShortMsg_presult__isset {
  _ThriftMessage_sendShortMsg_presult__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendShortMsg_presult__isset;

class ThriftMessage_sendShortMsg_presult {
 public:


  virtual ~ThriftMessage_sendShortMsg_presult() noexcept;
  ShortMessage* success;

  _ThriftMessage_sendShortMsg_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _ThriftMessage_sendLargeMsg_args__isset {
  _ThriftMessage_sendLargeMsg_args__isset() : lrgMsg(false) {}
  bool lrgMsg :1;
} _ThriftMessage_sendLargeMsg_args__isset;

class ThriftMessage_sendLargeMsg_args {
 public:

  ThriftMessage_sendLargeMsg_args(const ThriftMessage_sendLargeMsg_args&);
  ThriftMessage_sendLargeMsg_args& operator=(const ThriftMessage_sendLargeMsg_args&);
  ThriftMessage_sendLargeMsg_args() noexcept {
  }

  virtual ~ThriftMessage_sendLargeMsg_args() noexcept;
  LargeMessage lrgMsg;

  _ThriftMessage_sendLargeMsg_args__isset __isset;

  void __set_lrgMsg(const LargeMessage& val);

  bool operator == (const ThriftMessage_sendLargeMsg_args & rhs) const
  {
    if (!(lrgMsg == rhs.lrgMsg))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendLargeMsg_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendLargeMsg_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_sendLargeMsg_pargs {
 public:


  virtual ~ThriftMessage_sendLargeMsg_pargs() noexcept;
  const LargeMessage* lrgMsg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendLargeMsg_result__isset {
  _ThriftMessage_sendLargeMsg_result__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendLargeMsg_result__isset;

class ThriftMessage_sendLargeMsg_result {
 public:

  ThriftMessage_sendLargeMsg_result(const ThriftMessage_sendLargeMsg_result&);
  ThriftMessage_sendLargeMsg_result& operator=(const ThriftMessage_sendLargeMsg_result&);
  ThriftMessage_sendLargeMsg_result() noexcept {
  }

  virtual ~ThriftMessage_sendLargeMsg_result() noexcept;
  LargeMessage success;

  _ThriftMessage_sendLargeMsg_result__isset __isset;

  void __set_success(const LargeMessage& val);

  bool operator == (const ThriftMessage_sendLargeMsg_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ThriftMessage_sendLargeMsg_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_sendLargeMsg_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ThriftMessage_sendLargeMsg_presult__isset {
  _ThriftMessage_sendLargeMsg_presult__isset() : success(false) {}
  bool success :1;
} _ThriftMessage_sendLargeMsg_presult__isset;

class ThriftMessage_sendLargeMsg_presult {
 public:


  virtual ~ThriftMessage_sendLargeMsg_presult() noexcept;
  LargeMessage* success;

  _ThriftMessage_sendLargeMsg_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class ThriftMessage_ping_args {
 public:

  ThriftMessage_ping_args(const ThriftMessage_ping_args&) noexcept;
  ThriftMessage_ping_args& operator=(const ThriftMessage_ping_args&) noexcept;
  ThriftMessage_ping_args() noexcept {
  }

  virtual ~ThriftMessage_ping_args() noexcept;

  bool operator == (const ThriftMessage_ping_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const ThriftMessage_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_ping_pargs {
 public:


  virtual ~ThriftMessage_ping_pargs() noexcept;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_ping_result {
 public:

  ThriftMessage_ping_result(const ThriftMessage_ping_result&) noexcept;
  ThriftMessage_ping_result& operator=(const ThriftMessage_ping_result&) noexcept;
  ThriftMessage_ping_result() noexcept {
  }

  virtual ~ThriftMessage_ping_result() noexcept;

  bool operator == (const ThriftMessage_ping_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const ThriftMessage_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftMessage_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ThriftMessage_ping_presult {
 public:


  virtual ~ThriftMessage_ping_presult() noexcept;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class ThriftMessageClient : virtual public ThriftMessageIf {
 public:
  ThriftMessageClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  ThriftMessageClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t sendInt(const IntMessage& intMsg) override;
  void send_sendInt(const IntMessage& intMsg);
  int32_t recv_sendInt();
  void sendStr(std::string& _return, const StringMessage& strMsg) override;
  void send_sendStr(const StringMessage& strMsg);
  void recv_sendStr(std::string& _return);
  double sendDouble(const DoubleMessage& doubleMsg) override;
  void send_sendDouble(const DoubleMessage& doubleMsg);
  double recv_sendDouble();
  void sendShortMsg(ShortMessage& _return, const ShortMessage& srtMsg) override;
  void send_sendShortMsg(const ShortMessage& srtMsg);
  void recv_sendShortMsg(ShortMessage& _return);
  void sendLargeMsg(LargeMessage& _return, const LargeMessage& lrgMsg) override;
  void send_sendLargeMsg(const LargeMessage& lrgMsg);
  void recv_sendLargeMsg(LargeMessage& _return);
  void ping() override;
  void send_ping();
  void recv_ping();
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class ThriftMessageProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<ThriftMessageIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext) override;
 private:
  typedef  void (ThriftMessageProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_sendInt(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_sendStr(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_sendDouble(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_sendShortMsg(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_sendLargeMsg(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  ThriftMessageProcessor(::std::shared_ptr<ThriftMessageIf> iface) :
    iface_(iface) {
    processMap_["sendInt"] = &ThriftMessageProcessor::process_sendInt;
    processMap_["sendStr"] = &ThriftMessageProcessor::process_sendStr;
    processMap_["sendDouble"] = &ThriftMessageProcessor::process_sendDouble;
    processMap_["sendShortMsg"] = &ThriftMessageProcessor::process_sendShortMsg;
    processMap_["sendLargeMsg"] = &ThriftMessageProcessor::process_sendLargeMsg;
    processMap_["ping"] = &ThriftMessageProcessor::process_ping;
  }

  virtual ~ThriftMessageProcessor() {}
};

class ThriftMessageProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  ThriftMessageProcessorFactory(const ::std::shared_ptr< ThriftMessageIfFactory >& handlerFactory) noexcept :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo) override;

 protected:
  ::std::shared_ptr< ThriftMessageIfFactory > handlerFactory_;
};

class ThriftMessageMultiface : virtual public ThriftMessageIf {
 public:
  ThriftMessageMultiface(std::vector<std::shared_ptr<ThriftMessageIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~ThriftMessageMultiface() {}
 protected:
  std::vector<std::shared_ptr<ThriftMessageIf> > ifaces_;
  ThriftMessageMultiface() {}
  void add(::std::shared_ptr<ThriftMessageIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t sendInt(const IntMessage& intMsg) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sendInt(intMsg);
    }
    return ifaces_[i]->sendInt(intMsg);
  }

  void sendStr(std::string& _return, const StringMessage& strMsg) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sendStr(_return, strMsg);
    }
    ifaces_[i]->sendStr(_return, strMsg);
    return;
  }

  double sendDouble(const DoubleMessage& doubleMsg) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sendDouble(doubleMsg);
    }
    return ifaces_[i]->sendDouble(doubleMsg);
  }

  void sendShortMsg(ShortMessage& _return, const ShortMessage& srtMsg) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sendShortMsg(_return, srtMsg);
    }
    ifaces_[i]->sendShortMsg(_return, srtMsg);
    return;
  }

  void sendLargeMsg(LargeMessage& _return, const LargeMessage& lrgMsg) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sendLargeMsg(_return, lrgMsg);
    }
    ifaces_[i]->sendLargeMsg(_return, lrgMsg);
    return;
  }

  void ping() override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping();
    }
    ifaces_[i]->ping();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class ThriftMessageConcurrentClient : virtual public ThriftMessageIf {
 public:
  ThriftMessageConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  ThriftMessageConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t sendInt(const IntMessage& intMsg) override;
  int32_t send_sendInt(const IntMessage& intMsg);
  int32_t recv_sendInt(const int32_t seqid);
  void sendStr(std::string& _return, const StringMessage& strMsg) override;
  int32_t send_sendStr(const StringMessage& strMsg);
  void recv_sendStr(std::string& _return, const int32_t seqid);
  double sendDouble(const DoubleMessage& doubleMsg) override;
  int32_t send_sendDouble(const DoubleMessage& doubleMsg);
  double recv_sendDouble(const int32_t seqid);
  void sendShortMsg(ShortMessage& _return, const ShortMessage& srtMsg) override;
  int32_t send_sendShortMsg(const ShortMessage& srtMsg);
  void recv_sendShortMsg(ShortMessage& _return, const int32_t seqid);
  void sendLargeMsg(LargeMessage& _return, const LargeMessage& lrgMsg) override;
  int32_t send_sendLargeMsg(const LargeMessage& lrgMsg);
  void recv_sendLargeMsg(LargeMessage& _return, const int32_t seqid);
  void ping() override;
  int32_t send_ping();
  void recv_ping(const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif