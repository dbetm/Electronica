library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
-- Cuatro entradas, cada par a una AND y ambas salidas de la AND a una OR.
entity evilFace is
    Port ( a1 : in  STD_LOGIC;
           a2 : in  STD_LOGIC;
           b1 : in  STD_LOGIC;
           b2 : in  STD_LOGIC;
           s : out  STD_LOGIC);
end evilFace;

architecture Componente of evilFace is
-- Declaramos las compuertas que necesitamos como componentes.
component and_gate is 
	Port(a: in  STD_LOGIC;
        b: in  STD_LOGIC;
        s: out  STD_LOGIC);
end component;

component OR_gate is
	Port(a: in  STD_LOGIC;
        b: in  STD_LOGIC;
        s: out  STD_LOGIC);
end component;
-- Terminamos la declaración de las compuertas.

-- Declaramos algunas señales auxiliares.
signal	s1, s2: STD_LOGIC;

begin
-- Vemos los componentes declarados como cajas negras y hacemos una especie de instancia (mapear).
AND1: and_gate port map(a1, a2, s1);
AND2: and_gate port map(b1, b2, s2);
OR1: OR_gate port map(s1, s2, s);

end Componente;

