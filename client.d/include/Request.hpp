//
// Created by alice on 27/06/17.
//

#ifndef CLIENT_D_REQUEST_HPP
#define CLIENT_D_REQUEST_HPP

namespace zappy {
    typedef enum {
        FORWARD = 0,
        RIGHT,
        LEFT,
        LOOK,
        BROADCAST,
        NOOP
    } RequestType;

    template<typename T>
    class Request {
    public:
        Request(RequestType);

        ~Request();

    protected:
        RequestType _type;
        T _data;
    };
}

#endif //CLIENT_D_REQUEST_HPP
