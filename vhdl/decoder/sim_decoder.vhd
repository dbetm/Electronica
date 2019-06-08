LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY decoder1 IS
END decoder1;
 
ARCHITECTURE behavior OF decoder1 IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT decoder
    PORT(
         A : IN  std_logic;
         B : IN  std_logic;
         R : IN  std_logic;
         S : OUT  std_logic_vector(3 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic := '0';
   signal B : std_logic := '0';
   signal R : std_logic := '0';

 	--Outputs
   signal S : std_logic_vector(3 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   -- constant <clock>_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: decoder PORT MAP (
          A => A,
          B => B,
          R => R,
          S => S
        );

		-- Testing
		R <= '0' after 0 ns, '1' after 100 ns;
		A <= '1' after 100 ns, '0' after 200 ns;
		B <= '0' after 100 ns, '1' after 200 ns;
END;
