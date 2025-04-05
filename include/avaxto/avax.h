#ifndef AVAXTO_AVAX
#define AVAXTO_AVAX

// constants from network/network.go
#define defaultInitialReconnectDelay 1
#define defaultMaxReconnectDelay     (60 * 60)
#define DefaultMaxMessageSize        (1 << 21)
#define defaultSendQueueSize         (1 << 10)
#define defaultMaxNetworkPendingSendBytes (1 << 29) // 512MB
#define defaultNetworkPendingSendBytesToRateLimit        (defaultMaxNetworkPendingSendBytes / 4)
#define defaultMaxClockDifference    60
#define defaultPeerListGossipSpacing 60
#define defaultPeerListGossipSize    100
#define defaultPeerListStakerGossipFraction 2
#define defaultGetVersionTimeout     2
#define defaultAllowPrivateIPs       true
#define defaultGossipSize            50
#define defaultPingPongTimeout       60
#define defaultPingFrequency         (3 * defaultPingPongTimeout / 4)


#endif