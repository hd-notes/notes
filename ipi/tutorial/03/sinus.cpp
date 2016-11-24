/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  sinus.cpp -- Sinusberechung über Talyorentwicklung
*/

#include "common.h"

constexpr f64 pi = 3.14159265358979323;

namespace ipi {
	// Extrem schlechte implementation von tquot, aber für die Aufgabe
	// ausreichend
	const inline auto tquot(const f64 x) noexcept -> f64 { return (i32)x; }

	const inline auto fmod(const f64 a, const f64 b) -> f64 {
		return a - b * tquot(a / b);
	}

	const inline auto taylor_sin(const f64 x) noexcept -> f64 {
		return x - 0.16666666666666666666 * (x * x * x);
	}

	const inline auto degrees_to_rad(const f64 x) noexcept -> f64 {
		return (x / 180) * pi;
	}

	const inline auto pump_sin(const f64 s_) noexcept -> f64 {
		f64 s = ipi::fmod(pi + s_, 2.0 * pi) - pi;
		return 3 * s - 4 * s * s * s;
	}

	const inline auto my_sin(const f64 x) noexcept -> f64 {
		return (std::abs(x) <= degrees_to_rad(9)) ? taylor_sin(x)
												  : pump_sin(my_sin(x / 3));
    }
}

using namespace ipi;

/*
Tabelle zur Abweichung von taylor_sin
| Winkel in Grad | std::sin(i) | taylor_sin(i) | Betrag der Abweichung |
|----------------+-------------+---------------+-----------------------|
|              5 |   0.0871557 |     0.0871557 |           4.21674e-08 |
|             10 |    0.173648 |      0.173647 |           1.34862e-06 |
|             20 |     0.34202 |      0.341977 |           4.30622e-05 |
|             45 |    0.707107 |      0.704653 |            0.00245413 |
|             90 |           1 |      0.924832 |             0.0751678 |
|            135 |    0.707107 |      0.176066 |              0.531041 |
|            180 | 1.22465e-16 |      -2.02612 |               2.02612 |
|            225 |   -0.707107 |       -6.1662 |               5.45909 |
|            270 |          -1 |      -12.7286 |               11.7286 |
|            315 |   -0.707107 |      -22.1979 |               21.4908 |

Die Näherung hat einen Fehler von kleiner als 1e-6 bis zu x0 = 9°:
9°: |taylor_sin - std::sin| = 7.65e-7 (gerundet)
10°: |taylor_sin - std::sin| = 1.35e-6 > 1e-6 (gerundet)

Tabelle zur Abweichung von my_sin
| Winkel in Grad | std::sin(i) | taylor_sin(i) | Betrag der Abweichung |
|----------------+-------------+---------------+-----------------------|
|              5 |   0.0871557 |     0.0871557 |           4.21674e-08 |
|             10 |    0.173648 |      0.173648 |           1.64351e-08 |
|             20 |     0.34202 |       0.34202 |            5.0427e-07 |
|             45 |    0.707107 |      0.707107 |           2.69377e-07 |
|             90 |           1 |             1 |           1.13243e-14 |
|            135 |    0.707107 |      0.707108 |            8.0813e-07 |
|            180 | 1.22465e-16 |   4.82969e-06 |           4.82969e-06 |
|            225 |   -0.707107 |     -0.707096 |           1.04603e-05 |
|            270 |          -1 |            -1 |           1.02141e-13 |
|            315 |   -0.707107 |     -0.707107 |           6.89059e-07 |

Tabelle zur Abweichung vom verbesserten my_sin
| Winkel in Grad |  std::sin(i) | taylor_sin(i) | Betrag der Abweichung |
|----------------+--------------+---------------+-----------------------|
|              5 |    0.0871557 |     0.0871557 |           4.21674e-08 |
|             -5 |   -0.0871557 |    -0.0871557 |           4.21674e-08 |
|             10 |     0.173648 |      0.173648 |           1.64351e-08 |
|            -10 |    -0.173648 |     -0.173648 |           1.64351e-08 |
|             20 |      0.34202 |       0.34202 |            5.0427e-07 |
|            -20 |     -0.34202 |      -0.34202 |            5.0427e-07 |
|             45 |     0.707107 |      0.707107 |           2.69377e-07 |
|            -45 |    -0.707107 |     -0.707107 |           2.69377e-07 |
|             90 |            1 |             1 |           1.13243e-14 |
|            -90 |           -1 |            -1 |           1.13243e-14 |
|            135 |     0.707107 |      0.707108 |            8.0813e-07 |
|           -135 |    -0.707107 |     -0.707108 |            8.0813e-07 |
|            180 |  1.22465e-16 |   4.82969e-06 |           4.82969e-06 |
|           -180 | -1.22465e-16 |  -4.82969e-06 |           4.82969e-06 |
|            225 |    -0.707107 |     -0.707096 |           1.04603e-05 |
|           -225 |     0.707107 |      0.707096 |           1.04603e-05 |
|            270 |           -1 |            -1 |           1.02141e-13 |
|           -270 |            1 |             1 |           1.02141e-13 |
|            315 |    -0.707107 |     -0.707107 |           6.89059e-07 |
|           -315 |     0.707107 |      0.707107 |           6.89059e-07 |
*/

int main(){
	/*
	for(auto j : {5, 10, 20, 45, 90, 135, 180, 225, 270, 315}) {
			auto i = degrees_to_rad(j);
			std::cout << "| " << j << " | " << std::sin(i) << " | " << my_sin(i)
							  << " | " << std::abs(std::sin(i) - my_sin(i)) << "
	|"
							  << std::endl;
			i = degrees_to_rad(-j);
			std::cout << "| " << -j << " | " << std::sin(i) << " | " <<
	my_sin(i)
							  << " | " << std::abs(std::sin(i) - my_sin(i)) << "
	|"
							  << std::endl;
    }
	*/
} *
