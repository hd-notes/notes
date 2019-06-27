from constant import *

a = 3.61 * unit.angstrom
e_F = (unit.ħ**2 / (2 * unit.m_e)) * (((3.0 / 2.0) * unit.π**2 / a**3))**(2.0/3.0)
e_F = 4 * e_F # 4 atom with 1 electron each per unit cell
print(e_F.to(unit.electron_volt))
print((e_F / unit.boltzmann_constant).to(unit.kelvin))

γ = unit.π**2 * unit.avogadro_number * unit.boltzmann_constant**2 / (2.0 * e_F)
print(γ.to(unit.joule / unit.mol / unit.kelvin**2))

β = 12 * unit.π**4 * .2 * unit.avogadro_number * unit.boltzmann_constant * (345 * unit.kelvin)**(-3)
print(β.to(unit.joule / unit.mol / unit.kelvin**4))
