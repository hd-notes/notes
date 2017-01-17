/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  sort.cpp -- Insertion Sort implemenation
*/

#include "common.h"

template <typename T, typename CMP>
void insertion_sort(vec<T> & v, const CMP cmp) noexcept {
    for(u32 i = 0; i < v.size(); i++) {
        T   current = v[i];
        i32 j       = i;
        while(j > 0) {
            if(cmp(v[j - 1], current)) { break; }
            v[j] = v[j - 1];
            j--;
        }
        v[j] = current;
    }
}

template <typename Iterator, typename CMP>
void insertion_sort(Iterator begin, Iterator end, const CMP cmp) noexcept {
    auto beginning = begin;

    while(begin != end) {
        auto current   = *begin;
        auto iter_this = begin;

        while(iter_this > beginning) {
            auto iter_before = iter_this;
            iter_before--;

            if(cmp(*iter_before, current)) { break; }
            *iter_this = *iter_before;
            iter_this--;
        }

        *iter_this = current;
        begin++;
    }
}

template <typename T, typename CMP>
bool check_sorted(vec<T> & v, const CMP cmp) noexcept {
    for(u32 i = 1; i < v.size(); i++) {
        if(cmp(v[i], v[i - 1])) { return false; }
    }

    return true;
}

template <typename Iterator, typename CMP>
bool check_sorted(Iterator begin, Iterator end, const CMP cmp) noexcept {
    auto last_iter = begin;

    if(begin == end) { return true; }

    while(++begin != end) {
        if(cmp(*begin, *last_iter)) { return false; }

        last_iter++;
    }

    return true;
}

struct timed_block {
    inline timed_block() noexcept
        : begin(chrono::high_resolution_clock::now()) {}

    template <typename T>
    inline T get_time() noexcept {
        return chrono::duration<T>(chrono::high_resolution_clock::now() - begin)
            .count();
    }

    template <typename T>
    inline operator T() noexcept {
        return get_time<T>();
    }

    template <typename T, typename Functor>
    static inline T time(Functor f) noexcept {
        timed_block t;
        f();
        return t;
    }

private:
    const chrono::high_resolution_clock::time_point begin;
};

auto cmp = [](auto a, auto b) { return a < b; };

template <typename T>
f64 insertion_sort_best_time(i32 size) noexcept {
    vec<T> v(size);
    iota(v.begin(), v.end(), T());

    return timed_block::time<f64>(
        [&]() { insertion_sort(v.begin(), v.end(), cmp); });
}

template <typename T>
f64 insertion_sort_worst_time(i32 size) noexcept {
    vec<T> v(size);
    iota(v.begin(), v.end(), T());
    reverse(v.begin(), v.end());

    return timed_block::time<f64>(
        [&]() { insertion_sort(v.begin(), v.end(), cmp); });
}

template <typename T>
f64 insertion_sort_typical_time(i32 size) noexcept {
    vec<T> v(size);
    iota(v.begin(), v.end(), T());
    random_shuffle(v.begin(), v.end());

    return timed_block::time<f64>(
        [&]() { insertion_sort(v.begin(), v.end(), cmp); });
}

template <typename T>
f64 std_sort_time(i32 size) noexcept {
    vec<T> v(size);
    iota(v.begin(), v.end(), T());
    random_shuffle(v.begin(), v.end());

    return timed_block::time<f64>(
        [&]() { std::sort(v.begin(), v.end(), cmp); });
}

struct sorting_algorithm {
    function<f64(i32)> f;
    function<i32(i32)> complexity;
    string             name;
    i32                base_size;
    f64                increment;
};

struct timing_record {
    i32 size;
    f64 time;
};

std::ostream & operator<<(std::ostream &        out,
                          const timing_record & v) noexcept {
    return out << "{" << v.size << ", " << v.time << "}";
}

template <typename Iterator>
inline auto average(Iterator begin, Iterator end) noexcept {
    typename iterator_traits<Iterator>::value_type zero{};
    auto sum = accumulate(begin, end, zero);
    return sum / distance(begin, end);
}

i32 main() {
    vec<f64> nums = {1, 1, 2, 2, 3, 4, 5, 5, 10, 100};

    auto cmp = [](auto a, auto b) { return a > b; };
    for(i32 i = 0; i < 10; i++) {
        insertion_sort(nums, cmp);
        insertion_sort(nums.begin(), nums.end(), cmp);
        assert(check_sorted(nums, cmp));
        assert(check_sorted(nums.begin(), nums.end(), cmp));
        random_shuffle(nums.begin(), nums.end());
        assert(!check_sorted(nums, cmp));
        assert(!check_sorted(nums.begin(), nums.end(), cmp));
    }

    auto i = 0;
    while(true) {
        auto itime = insertion_sort_typical_time<double>(i);
        auto stime = std_sort_time<double>(i);
		if(itime > stime) {
			cout << i << endl;
			cout << itime << endl;
			cout << stime << endl;

			break;
		}
        i++;
    }

    auto linear    = [](auto a) { return a; };
    auto quadratic = [](auto a) { return a * a; };
    auto nlogn     = [](auto a) { return a * log(a); };

    array<sorting_algorithm, 4> algos = {
        {{insertion_sort_best_time<double>, linear, "best case", 1000000, 1.2},
         {insertion_sort_worst_time<double>, quadratic, "worst case", 2000,
          1.07},
         {insertion_sort_typical_time<double>, quadratic, "typical case", 5000,
          1.07},
         {std_sort_time<double>, nlogn, "std::sort", 100000, 1.07}}};

    for(const auto & algo : algos) {
        vec<timing_record> timings;
        for(i32 i = 0; i < 25; i++) {
            i32      size = algo.base_size * pow(algo.increment, i);
            vec<f64> single_timings;

            for(i32 j = 0; j < 3; j++) {
                single_timings.push_back(algo.f(size));
            }

            timings.push_back({size, *min_element(single_timings.begin(),
                                                  single_timings.end())});
        }

        vec<f64> c(timings.size());
        transform(
            timings.begin(), timings.end(), c.begin(),
            [&](timing_record r) { return r.time / algo.complexity(r.size); });

        cout << algo.name << ":" << endl;
        cout << timings << endl;
        cout << c << endl;
        cout << "average: " << average(c.begin(), c.end()) << endl;
    }
}
