#ifndef _UTILS_NINTACO_API_HPP
#define _UTILS_NINTACO_API_HPP

#include <nintaco/nintaco.hpp>

namespace nintaco
{
    class Api
    {
        private:
            NintacoAPI* api = nullptr;

        private:
            Api() = default;

        public:
            void init(NintacoAPI* api);
            NintacoAPI* get_api() const;

        public:
            Api(const Api &other) = delete;
            Api operator=(const Api &other) = delete;

            static Api &API()
            {
                static Api singleton;
                return singleton;
            }
    };
}

#endif