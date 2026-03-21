#ifndef CAFFEINECOMPONENT_HPP
#define CAFFEINECOMPONENT_HPP

#include <type_traits>

struct CaffeineComponent{};

template<typename ComponentType>
concept Component = std::is_base_of_v<CaffeineComponent, ComponentType>;

#endif //CAFFEINECOMPONENT_HPP
