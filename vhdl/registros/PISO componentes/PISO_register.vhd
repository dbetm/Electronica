library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Registro PISO (Parallel input - Serial output)
-- Si la bandera de CargaDesplazamiento es '0', entonces, carga los datos de D en forma paralela
-- Si la bandera de CargaDesplazamiento es '1', entonces, hace el desplazamiento y la salida es de forma serial sobre el flip-flop del extremo derecho

entity PISO_register is
    Port (D : in  STD_LOGIC_VECTOR (0 to 3);
          CargaDesplazamiento : in  STD_LOGIC;
          clk : in  STD_LOGIC;
          salida : out  STD_LOGIC);
end PISO_register;

architecture Registro of PISO_register is

-- ### Inicia: Declaración de componentes.
component flipFlop_D is
	Port (d : in  STD_LOGIC;
         clk : in  STD_LOGIC;
         q : out  STD_LOGIC);
end component;

component evilFace is 
	Port (a1 : in  STD_LOGIC;
         a2 : in  STD_LOGIC;
         b1 : in  STD_LOGIC;
         b2 : in  STD_LOGIC;
         s : out  STD_LOGIC);
end component;

component and_gate is 
	Port(a: in  STD_LOGIC;
        b: in  STD_LOGIC;
        s: out  STD_LOGIC);
end component;
-- ### Termina: Declaración de componentes.
signal q0, q1, q2, s0, s1, s2, s3: STD_LOGIC; -- Señales auxiliares.
begin
AND0: and_gate port map (D(0), not CargaDesplazamiento, s0);
FFD0: flipFlop_D port map (s0, clk, q0);
EF0: evilFace port map (q0, CargaDesplazamiento, not CargaDesplazamiento, D(1), s1);
FFD1: flipFlop_D port map (s1, clk, q1);
EF1: evilFace port map (q1, CargaDesplazamiento, not CargaDesplazamiento, D(2), s2);
FFD2: flipFlop_D port map (s2, clk, q2);
EF2: evilFace port map (q2, CargaDesplazamiento, not CargaDesplazamiento, D(3), s3);
FFD3: flipFlop_D port map (s3, clk, salida);

end Registro;

