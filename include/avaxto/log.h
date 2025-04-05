#ifndef AVAXTO_LOG
#define AVAXTO_LOG

enum avax_log_message_type_e {
    AVAXTO_MESSAGE_INFO,
    AVAXTO_MESSAGE_ERROR,
    AVAXTO_MESSAGE_WARNING,
    AVAXTO_MESSAGE_DEBUG,
};

void avax_log(const char *msg, enum avax_log_message_type_e typ);



#endif