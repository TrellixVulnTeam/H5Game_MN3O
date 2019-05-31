#ifndef PW_MESSAGE_PROCESSOR_H
#define PW_MESSAGE_PROCESSOR_H

#include "pw_def.h"
#include <tbb/concurrent_queue.h>

namespace pwutils
{
    class PostedMessage
    {
    public:
        int64   msgid;
        int64   msglen;
        void*   object;
        char    buf[1];
    };

    class MessageProcessor
    {
    public:
        virtual ~MessageProcessor();
    public:
        void Post(PostedMessage* msg);
        void HandleMessages();
    protected:
        virtual void Process(PostedMessage* msg);
    protected:
        PostedMessage* Recv();
    protected:
        typedef tbb::concurrent_queue<PostedMessage*> CollectionMessagesT;
    protected:
        CollectionMessagesT m_vMsgs;
    };
}

#endif // PW_MESSAGE_PROCESSOR_H
