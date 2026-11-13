using va_list = char*;

#include <cstddef> // IWYU pragma: keep
#include <array> // IWYU pragma: keep
#include <utility> // IWYU pragma: keep
#include <tuple> // IWYU pragma: keep
#include <vector> // IWYU pragma: keep
#include <map> // IWYU pragma: keep
#include <unordered_map> // IWYU pragma: keep
#include <set> // IWYU pragma: keep
#include <unordered_set> // IWYU pragma: keep
#include <list> // IWYU pragma: keep
#include <string> // IWYU pragma: keep

// Types introduced by the GD 2.209 bindings that the layout stubs above do
// not model yet. Only their sizes/alignments matter for type import, and
// these are ABI-stable per platform.
namespace std
{
	struct atomic_bool
	{
		bool _My_val;
	};

#if defined(BROMAIDA_IS_PLATFORM_MACHO) && BROMAIDA_IS_PLATFORM_MACHO
	// libc++ std::mutex wraps a 64-byte pthread_mutex_t
	class mutex { long long _Mtx[8]; };
#elif defined(BROMAIDA_IS_PLATFORM_ANDROID) && BROMAIDA_IS_PLATFORM_ANDROID
#if defined(BROMAIDA_PLATFORM_ANDROID64)
	// bionic pthread_mutex_t is 40 bytes on 64-bit
	class mutex { long long _Mtx[5]; };
#else
	// bionic pthread_mutex_t is 4 bytes on 32-bit
	class mutex { int _Mtx; };
#endif
#else
	// MSVC std::mutex wraps a single native handle
	class mutex { void* _Mtx; };
#endif
}
