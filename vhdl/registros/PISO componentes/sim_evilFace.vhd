LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY sim_evilFace IS
END sim_evilFace;
 
ARCHITECTURE behavior OF sim_evilFace IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT evilFace
    PORT(
         a1 : IN  std_logic;
         a2 : IN  std_logic;
         b1 : IN  std_logic;
         b2 : IN  std_logic;
         s : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal a1 : std_logic := '0';
   signal a2 : std_logic := '0';
   signal b1 : std_logic := '0';
   signal b2 : std_logic := '0';

 	--Outputs
   signal s : std_logic;
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   -- constant <clock>_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: evilFace PORT MAP (
          a1 => a1,
          a2 => a2,
          b1 => b1,
          b2 => b2,
          s => s
        );
		  
	-- algunas pruebas tomadas de la tabla de verdad
   a1 <= '0' after 100 ns, '1' after 300 ns;
	a2 <= '0' after 100 ns, '1' after 200 ns, '0' after 300 ns, '1' after 400 ns;
	b1 <= '1' after 100 ns, '1' after 200 ns, '0' after 400 ns;
	b2 <= '1' after 100 ns, '1' after 400 ns;

END;
