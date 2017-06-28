//
// Created by Jean-Adrien on 27/06/17.
//

#ifndef CLIENT_D_REQUEST_HPP
#define CLIENT_D_REQUEST_HPP

namespace zappy {
    typedef enum {
        FORWARD,
        RIGHT,
        LEFT,
        LOOK,
        BROADCAST,
        NOOP
    } RequestType;

    template<class T>
    class Request {
    public:
        Request();

        ~Request();

    protected:
        RequestType _type;
    };
}

#endif //CLIENT_D_REQUEST_HPP
