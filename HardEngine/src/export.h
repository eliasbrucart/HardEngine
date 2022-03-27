#ifndef EXPORT_H

#ifdef HARD_ENGINE_EXPORT
#define HARD_ENGINE_API __declspec(dllimport)
#else
#define HARD_ENGINE_API __declspec(dllexport)
#endif //HARD ENGINE EXPORT

#endif //EXPORT_H