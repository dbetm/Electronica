library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dig_clk is
    Port ( clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           display : out  STD_LOGIC_VECTOR (6 downto 0);
           digito : out  STD_LOGIC_VECTOR (3 downto 0));
end dig_clk;

architecture Behavioral of dig_clk is
-- Declaración de las señales empleadas.
signal clk1s, segundos, unidades_minutos, decenas_minutos, unidades_horas : STD_LOGIC;
signal clk600 : STD_LOGIC;
signal deco1, deco2, deco3, deco4, dis: STD_LOGIC_VECTOR(6 downto 0);
signal n: STD_LOGIC_VECTOR(3 downto 0);
signal cont1 : natural range 0 to 50000001;
signal cont2 : natural range 0 to 61;
signal cont3 : natural range 0 to 10;
signal cont4 : natural range 0 to 7;
signal cont5 : natural range 0 to 10;
signal cont6 : natural range 0 to 3;
signal cont600: natural range 0 to 601;
signal cc : natural range 0 to 4;
begin


-- Acondicionamiento de la señal de reloj a 1Hz (1 segundo).
a_second: process(clk, reset)
begin
	if(reset = '1') then
		cont1 <= 0;
		clk1s <= '0';
	elsif (clk'event and clk = '1') then 
		if (cont1 = 50000000) then 
			cont1 <= 0;
			clk1s <='1';
		else
			cont1 <= cont1 + 1;				
			clk1s <= '0';
			end if;
	end if;
end process;


-- El siguiente process lleva un conteo para los segundos (unidades y decenas, del 0 al 60).
seconds: process(clk1s, reset)
begin
	if(reset = '1') then
		cont2 <= 0;
		segundos <= '0';
	elsif(clk1s'event and clk1s = '1') then
		if (cont2 = 60) then
			cont2 <= 0;
			segundos <= '1';
		else 
			cont2 <= cont2 + 1;
			segundos <= '0';
		end if;
	end if;
end process;


-- El siguiente process lleva un conteo para las unidades de los minutos, del 0 al 9.
units_minutes: process(segundos, reset)
begin
	if(reset = '1') then
		cont3 <= 0;
		unidades_minutos <= '0';
	elsif(segundos'event and segundos = '1') then
		if (cont3 = 9) then
			cont3 <= 0;
			unidades_minutos <= '1';
		else 
			cont3 <= cont3 + 1;
			unidades_minutos <= '0';
		end if;
	end if;
end process;


-- El siguiente process lleva un conteo para las decenas de los minutos, del 0 al 6.
tens_minutes: process(unidades_minutos, reset)
begin
	if(reset = '1') then
		cont4 <= 0;
		decenas_minutos <= '0';
	elsif(unidades_minutos'event and unidades_minutos = '1') then
		if (cont4 = 6) then
			cont4 <= 0;
			decenas_minutos <= '1';
		else 
			cont4 <= cont4 + 1;
			decenas_minutos <= '0';
		end if;
	end if;
end process;


-- El siguiente process lleva un conteo para las unidades de las horas, del 0 al 9.
units_hours: process(decenas_minutos, reset)
begin
	if(reset = '1') then
		cont5 <= 0;
		unidades_horas <= '0';
	elsif(decenas_minutos'event and decenas_minutos = '1') then
		if (cont5 = 9) then
			cont5 <= 0;
			unidades_horas <= '1';
		else 
			cont5 <= cont5 + 1;
			unidades_horas <= '0';
		end if;
	end if;
end process;


-- El siguiente process lleva un conteo para las decenas de las horas, del 0 al 2.
tens_hours: process(unidades_horas, reset)
begin
	if(reset = '1') then
		cont6 <= 0;
	elsif(unidades_horas'event and unidades_horas = '1') then
		if (cont6 = 2 and cont5 = 4) then
			cont6 <= 0;
		else 
			cont6 <= cont6 + 1;
		end if;
	end if;
end process;


-- Para decodificar las unidades de los minutos
decodificador1: process(cont3)
begin
	case cont3 is
		when 0 => deco1 <= "1000000"; 
		when 1 => deco1 <= "1111001"; 
		when 2 => deco1 <= "0100100"; 	
		when 3 => deco1 <= "0110000"; 
		when 4 => deco1 <= "0011001";  
		when 5 => deco1 <= "0010010"; 
		when 6 => deco1 <= "0000010";  
		when 7 => deco1 <= "1111000"; 
		when 8 => deco1 <= "0000000"; 
		when 9 => deco1 <= "0010000"; 
		when others => deco1 <= "1111111"; 
	end case;
end process;


-- Para decodificar las decenas de los minutos
decodificador2: process(cont5)
begin
	case cont4 is
		when 0 => deco2 <= "1000000"; 
		when 1 => deco2 <= "1111001"; 
		when 2 => deco2 <= "0100100"; 	
		when 3 => deco2 <= "0110000"; 
		when 4 => deco2 <= "0011001";  
		when 5 => deco2 <= "0010010"; 
		when 6 => deco2 <= "0000010";  
		when others => deco2 <= "1111111"; 
	end case;
end process;


-- Para decodificar las unidades de las horas
decodificador3: process(cont5)
begin
	case cont5 is
		when 0 => deco3 <= "1000000"; 
		when 1 => deco3 <= "1111001"; 
		when 2 => deco3 <= "0100100"; 	
		when 3 => deco3 <= "0110000"; 
		when 4 => deco3 <= "0011001";  
		when 5 => deco3 <= "0010010"; 
		when 6 => deco3 <= "0000010";  
		when 7 => deco3 <= "1111000"; 
		when 8 => deco3 <= "0000000"; 
		when 9 => deco3 <= "0010000"; 
		when others => deco3 <= "1111111"; 
	end case;
end process;


-- Para decodificar las decenas de las horas
decodificador4: process(cont6)
begin
	case cont6 is
		when 0 => deco4 <= "1000000"; 
		when 1 => deco4 <= "1111001"; 
		when 2 => deco4 <= "0100100"; 	
		when others => deco4 <= "1111111"; 
	end case;
end process;

-- acondicionamiento de señal para el contador circular,
-- frecuencia de 83.33 kHz
signal600: process(clk)
begin
	if(clk'event and clk = '1') then
		if(cont600 = 600) then
			cont600 <= 0;
			clk600 <= '1';
		else 
			cont600 <= cont600 + 1;
		end if;
	end if;
end process;


contadorAnillo: process(clk600)
begin
	if(clk600'event and clk600 = '1') then
		if(cc = 3) then
			cc <= 0;
		else
		   cc <= cc + 1;
		end if;
	end if;
end process;


multiplexado: process(cc, deco1, deco2, deco3, deco4)
begin
	if(cc = 0) then
		dis <= deco1;
		n <= "1110";
	elsif(cc = 1) then
		dis <= deco2;
		n <= "1101";
	elsif(cc = 2) then
		dis <= deco3;
		n <= "1011";
	else
		dis <= deco4;
		n <= "0111";
	end if;
end process;

display <= dis;
digito <= n;

end Behavioral;

