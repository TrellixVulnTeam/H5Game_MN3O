#include "pw_message_processor.h"

namespace pwutils
{
    MessageProcessor::~MessageProcessor()
    {
        while(PostedMessage* msg = Recv())
        {
            free(msg);
        }
    }

    void MessageProcessor::Post(PostedMessage *msg)
    {
        m_vMsgs.push(msg);
    }

    PostedMessage* MessageProcessor::Recv()
    {
        PostedMessage* msg = NULL;
        if(m_vMsgs.try_pop(msg))
            return msg;
        return NULL;
    }

    void MessageProcessor::HandleMessages()
    {
        while(PostedMessage* msg = Recv())
        {
            this->Process(msg);
            free(msg);
        }
    }

    void MessageProcessor::Process(PostedMessage* msg)
    {

    }
}
