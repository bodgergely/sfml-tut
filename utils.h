#ifndef UTILS_H
#define UTILS_H

#include <SFML/Window.hpp>
#include <cstdio>
#include <cassert>

#define LOG(...) fprintf(stdout, __VA_ARGS__)
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__)

std::string event_type_str(const sf::Event& event);

#endif /* end of include guard: UTILS_H */
