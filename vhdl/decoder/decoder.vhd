library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Un decodificador que tiene 2 (n) entradas y 4 (2^n) salidas.
-- R es una bandera, que debe estar activada para permitir 
-- el funcionamiento del decodificador 2 a 4.

entity decoder is
    Port ( A : in  STD_LOGIC;
           B : in  STD_LOGIC;
           R : in  STD_LOGIC;
           S : out  STD_LOGIC_VECTOR (3 downto 0));
end decoder;

architecture Behavioral of decoder is

begin
	-- Dependiendo de las entradas, es la salida
	-- Básicamente son múltiples condiciones
	S <= "1000" when A = '0' and B = '0' and R = '1' else
		  "0100" when A = '0' and B = '1' and R = '1' else
		  "0010" when A = '1' and B = '0' and R = '1' else
		  "0001" when A = '1' and B = '1' and R = '1' else
		  "0000";

end Behavioral;

