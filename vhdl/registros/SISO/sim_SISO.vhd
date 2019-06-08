LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY sim_SISO IS
END sim_SISO;
 
ARCHITECTURE behavior OF sim_SISO IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT SISO
    PORT(
         entrada : IN  std_logic;
         clk : IN  std_logic;
         salida : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal entrada : std_logic := '0';
   signal clk : std_logic := '0';

 	--Outputs
   signal salida : std_logic;

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: SISO PORT MAP (
          entrada => entrada,
          clk => clk,
          salida => salida
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;

      -- stimulus
			-- En el registro se desea almacenar el dato 1011
		entrada <= '1';
		wait for 10 ns;
		
		entrada <= '1';
		wait for 10 ns;
		
		entrada <= '0';
		wait for 10 ns;
		
		entrada <= '1';
		wait for 10 ns;
		
			-- Con el fin de notar mejor la transferencia completa del dato
		entrada <= '0';
		wait for 10 ns;

      wait;
   end process;

END;
