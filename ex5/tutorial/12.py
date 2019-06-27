from constant import *
from numpy import *

# 25 mm 
# c^25 = 10
# 
# z = log(y) / log(c)
# 
# (log(1) - log(10)) / log(c) = 25
# 
# 18 mm

c = exp((log(1) - log(10)) / 25.0)

# (log(e-5) - log(x)) / log(c) = 18
ρ1 = exp(-(18 * log(c) - log(1e-5))) * unit.ohm * unit.meter
ρ2 = exp(-(4 * log(c) - log(1e-1))) * unit.ohm * unit.meter

T1inv = 0.001 / unit.kelvin
T2inv = 0.003 / unit.kelvin

Eg = 2 * unit.boltzmann_constant * log(ρ1 / ρ2) / (T1inv - T2inv)

print(Eg.to(unit.electron_volt))

# ρ1 = 

# EF = 5 * unit.boltzmann_constant * T + EV
# EA = 0.15 * Eg + EV

# T = 0.08 * Eg / unit.boltzmann_constant

# EF - EA = 5 * 0.05 * Eg - 0.15 * Eg 

gA = 1

nA = 5e23 / unit.meter**3

nA0 = nA * (gA * exp((5 * 0.05 - 0.15) / 0.08) + 1)**(-1)

nAm = nA - nA0
print(nAm)
