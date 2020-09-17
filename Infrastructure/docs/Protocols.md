# Amon Din Protocol

The Amon Din Protocol (ADP) defines a reliable service-oriented request-reply dialog between a pool of nodes each of which having the capability to both receive and send messages/signals to their peers. APD covers presence, heartbeating, and service-oriented request-reply processing. It is a modification from the Majordomo pattern defined in Chapter 4 of the Zero Message Queue Guide.

## License

## Change Process

This Specification is a free and open standard (see “Definition of a Free and Open Standard") and is governed by the Digital Standards Organization’s Consensus-Oriented Specification System (COSS) (see “Consensus Oriented Specification System").

## Language

The key words “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”, “SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this document are to be interpreted as described in RFC 2119 (see “Key words for use in RFCs to Indicate Requirement Levels").

## Goals

The goals of ADP are to:

-   Allow nodes to be act as both requestors and repliers.
-   Allow requests to be routed to node peers on the basis of abstract service names.
-   Allow both nodes to detect disconnection of the other peer, through the use of heartbeating.
-   Allow the broker to recover from dead or disconnected nodes.
-   Allow for disaster recovery and load balancing by including sockets for dual broker functionality.

## Message Definitions

### Client to Broker

MDP/Client is a strictly synchronous dialog initiated by the client (where ‘C’ represents the client, and ‘B’ represents the broker):

    Repeat:
        C: REQUEST
        B: REPLY

A REQUEST command consists of a multipart message of 4 or more frames, formatted on the wire as follows:

-   Frame 0: Empty (zero bytes, invisible to REQ application)
-   Frame 1: “MDPC01” (six bytes, representing MDP/Client v0.1)
-   Frame 2: Service name (printable string)
-   Frames 3+: Request body (opaque binary)

A REPLY command consists of a multipart message of 4 or more frames, formatted on the wire as follows:

-   Frame 0: Empty (zero bytes, invisible to REQ application)
-   Frame 1: “MDPC01” (six bytes, representing MDP/Client v0.1)
-   Frame 2: Service name (printable string)
-   Frames 3+: Reply body (opaque binary)

Clients SHOULD use a REQ socket when implementing a synchronous request-reply pattern. The REQ socket will silently create frame 0 for outgoing requests, and remove it for replies before passing them to the calling application. Clients MAY use a DEALER (XREQ) socket when implementing an asynchronous pattern. In that case the clients MUST create the empty frame 0 explicitly.

### Broker to Service

MDP/Worker is a mix of a synchronous request-reply dialog, initiated by the service worker, and an asynchronous heartbeat dialog that operates independently in both directions. This is the synchronous dialog (where ‘S’ represents the service worker, and ‘B’ represents the broker):

    S: READY
    Repeat:
        B: REQUEST
        S: REPLY

The asynchronous heartbeat dialog operates on the same sockets and works thus:

    Repeat:                 Repeat:
        S: HEARTBEAT            B: HEARTBEAT
        ...                     ...
    S: DISCONNECT           B: DISCONNECT

A READY command consists of a multipart message of 4 frames, formatted on the wire as follows:

-   Frame 0: Empty frame
-   Frame 1: “MDPW01” (six bytes, representing MDP/Worker v0.1)
-   Frame 2: 0x01 (one byte, representing READY)
-   Frame 3: Service name (printable string)

A REQUEST command consists of a multipart message of 6 or more frames, formatted on the wire as follows:

-   Frame 0: Empty frame
-   Frame 1: “MDPW01” (six bytes, representing MDP/Worker v0.1)
-   Frame 2: 0x02 (one byte, representing REQUEST)
-   Frame 3: Client address (envelope stack)
-   Frame 4: Empty (zero bytes, envelope delimiter)
-   Frames 5+: Request body (opaque binary)

A REPLY command consists of a multipart message of 6 or more frames, formatted on the wire as follows:

-   Frame 0: Empty frame
-   Frame 1: “MDPW01” (six bytes, representing MDP/Worker v0.1)
-   Frame 2: 0x03 (one byte, representing REPLY)
-   Frame 3: Client address (envelope stack)
-   Frame 4: Empty (zero bytes, envelope delimiter)
-   Frames 5+: Reply body (opaque binary)

A HEARTBEAT command consists of a multipart message of 3 frames, formatted on the wire as follows:

-   Frame 0: Empty frame
-   Frame 1: “MDPW01” (six bytes, representing MDP/Worker v0.1)
-   Frame 2: 0x04 (one byte, representing HEARTBEAT)

MD/Worker commands all start with an empty frame to allow consistent processing of client and worker frames in a broker, over a single socket. The empty frame has no other significance.
