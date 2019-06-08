--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY sim_a1_registro_con_mux IS
END sim_a1_registro_con_mux;
 
ARCHITECTURE behavior OF sim_a1_registro_con_mux IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT registro
    PORT(
         entrada : IN  std_logic_vector(7 downto 0);
         load : IN  std_logic;
         clk : IN  std_logic;
         reset : IN  std_logic;
         salida : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal entrada : std_logic_vector(7 downto 0) := (others => '0');
   signal load : std_logic := '0';
   signal clk : std_logic := '0';
   signal reset : std_logic := '0';

 	--Outputs
   signal salida : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: registro PORT MAP (
          entrada => entrada,
          load => load,
          clk => clk,
          reset => reset,
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
		entrada <= "10000000"; -- se define la entrada que se guarda en el registro
		load <= '1'; -- se habilita la entrada del nuevo dato
		wait for 100 ns;
		load <= '0'; -- se deshabilita la carga
		entrada <= "00000011"; -- no estará a la salida, si no que se mantiene '100000000'
		wait for 100 ns;
		 -- después de 15 segundos se va a resetear
		reset <= '1';
		wait for 100 ns;
		-- habilitamos la carga del nuevo dato
		reset <= '0';
		load <= '1';

      wait;
   end process;

END;
