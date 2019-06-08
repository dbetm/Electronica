LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
 
ENTITY sim_PISO IS
END sim_PISO;
 
ARCHITECTURE behavior OF sim_PISO IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT PISO_register
    PORT(
         D : IN  std_logic_vector(0 to 3);
         CargaDesplazamiento : IN  std_logic;
         clk : IN  std_logic;
         salida : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal D : std_logic_vector(0 to 3) := (others => '0');
   signal CargaDesplazamiento : std_logic := '0';
   signal clk : std_logic := '0';

 	--Outputs
   signal salida : std_logic;

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: PISO_register PORT MAP (
          D => D,
          CargaDesplazamiento => CargaDesplazamiento,
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

      -- insert stimulus here 
		D <= "1011";
		CargaDesplazamiento <= '0'; wait for 10 ns;
		CargaDesplazamiento <= '1';
      wait;
   end process;

END;
