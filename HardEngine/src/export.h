#ifndef EXPORT_H

#ifdef HARD_ENGINE_EXPORT
#define HARD_ENGINE_API __declspec(dllexport)
#else
#define HARD_ENGINE_API __declspec(dllimport)
#endif //HARD ENGINE EXPORT

#endif //EXPORT_H