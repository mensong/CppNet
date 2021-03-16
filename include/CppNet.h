#ifndef INCLUDE_CPPNET
#define INCLUDE_CPPNET

#include <memory>
#include "CppDefine.h"

namespace cppnet {

    class CCppNetImpl;
    // cppnet instace
    class CCppNet {
    public:
        CCppNet();
        ~CCppNet();
        // common
        // init cppnet library.
        // thread_num : the number of running threads.
        void Init(int32_t thread_num);

        // thread join
        void Join();

        // must set callback before listen
        void SetReadCallback(const read_call_back& func);
        void SetWriteCallback(const write_call_back& func);
        void SetDisconnectionCallback(const connection_call_back& func);

        //timer
        uint64_t SetTimer(int32_t interval, const timer_call_back& func, void* param = nullptr, bool always = false);
        void RemoveTimer(uint64_t timer_id);

        //server
        void SetAcceptCallback(const connection_call_back& func);
        bool ListenAndAccept(const std::string& ip, int16_t port);

        //client
        void SetConnectionCallback(const connection_call_back& func);

#ifndef __linux__
        // sync connection. 
        bool Connection(const std::string& ip, int16_t port, const char* buf, int32_t buf_len);
#endif
        bool Connection(const std::string& ip, int16_t port);
    private:
        std::shared_ptr<CCppNetImpl> _cppnet_instance;
    };
}

#endif