library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
-- ff's : flip-flops

-- Este es un registro (de corrimiento hacia la derecha) del tipo SISO, entrada en serie y salida en serie.
-- Es capaz de almacenar 4 bits, por lo cual emplea 4 flip-flops tipo D.
-- Los cambios ocurren cuando existe un flanco descendente en el ciclo de reloj.
-- Hecho por un estudiante que apenas está aprendiendo, cualquier sugerencia y/o corrección es bienvenida.

entity SISO is
    Port ( entrada : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           salida : out  STD_LOGIC);
end SISO;

architecture Registro of SISO is
signal registro: STD_LOGIC_VECTOR(3 downto 0); -- Declaramos un registro interno que actúa como 4 ff's
begin
	process(clk)
	begin
		if clk'event and clk = '1' then -- flanco descendente del ciclo de reloj
			registro <= entrada & registro(3 downto 1);
		end if;
-- La señal de salida corresponde al bit menos significativo, es decir al valor del flip-flop del extremo de la derecha
		salida <= registro(0); 
	end process;

end Registro;

