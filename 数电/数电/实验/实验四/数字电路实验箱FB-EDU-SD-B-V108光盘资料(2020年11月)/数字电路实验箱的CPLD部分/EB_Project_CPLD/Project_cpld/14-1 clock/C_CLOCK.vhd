library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
entity C_CLOCK is
port(
     clk:in std_logic;
     ctrlin:in std_logic_vector(2 downto 0);
     disp:out std_logic_vector(7 downto 0);--显示代码
     ledcs:out std_logic_vector(3 downto 0)--数码管片选
    );
end C_CLOCK;

architecture rtl of C_CLOCK is
signal start,stop,reset:std_logic;
signal key_temp0:std_logic_vector(2 downto 0);
signal N:std_logic_vector(3 downto 0);--键值缓存
signal keydown:std_logic;--按键 
signal ACC:std_logic_vector(23 downto 0);--初始化
signal hour10,hour1,min10,min1,sec10,sec1:std_logic_vector(3 downto 0);
SIGNAL clk_1k:std_logic;
signal data:std_logic_vector(3 downto 0);
signal flag:integer range 0 to 6;
signal timeclk:std_logic;

component led_disp is
 port(datain:in std_logic_vector(3 downto 0);
      dataout:out std_logic_vector(7 downto 0)
     );
end component;

begin

process(ctrlin,clk)
  variable cnt:integer range 0 to 2500000;
   begin
   if (ctrlin="111") then  cnt:=0;  --无键按下
     elsif (clk'event and clk='1')  then 
       if cnt>2499999 then cnt:=0;key_temp0<=ctrlin; --延时消抖,时间要足够才不会出错
       else  cnt:=cnt+1;
        end if;
  end if;
   case key_temp0 is
    when "110"=>start<='1';stop<='0';reset<='0';--开始
    when "101"=>start<='0';stop<='1';reset<='0';--停止
    when "011"=>start<='0';stop<='0';reset<='1';--置数
    when others=>start<='0';stop<='0';reset<='0';
   end case;
  end process;
  
 
   
CLK_1Khz:process(clk)--产生1k的扫描信号
    variable cnt:integer range 0 to 50000;
      begin
       if rising_edge(clk) then cnt:=cnt+1;
         if cnt<25000 then clk_1k<='1';
          elsif cnt<50000 then clk_1k<='0';
          else cnt:=0;clk_1k<='0';
        end if;
        end if;
 end process;
 
process (clk_1k)  --显示
  variable cnt2:std_logic_vector(3 downto 0);
begin 
   if clk_1k'event and clk_1k='1' then cnt2:=cnt2+1; 
--     if cnt2="0001" then 
--        ledcs<="01111111";
--        data<=hour10;
--     elsif cnt2="0010" then 
--        ledcs<="10111111";
--        data<=hour1;  
--     elsif cnt2="0011" then 
--        ledcs<="11011111";
--        data<="1010";  
     if cnt2="0001" then 
        ledcs<="0111";
        data<=min10;
     elsif cnt2="0010" then 
        ledcs<="1011";
        data<=min1;
--    elsif cnt2="0110" then 
--        ledcs<="11111011";
--        data<="1011";  
     elsif cnt2="0011" then 
        ledcs<="1101";
        data<=sec10;
     elsif cnt2="0100" then 
        ledcs<="1110";
        data<=sec1;
        cnt2:="0000";
     end if;
   end if;
end process;

process(clk)        --开始了时钟模块的程序
  variable cnt:integer range 0 to 50000000; --分频1s
  begin 
   if clk'event and clk='1' then cnt:=cnt+1;
     if cnt<25000000 then  timeclk<='1';
     elsif cnt<50000000 then timeclk<='0';
     else cnt:=0;timeclk<='0';
     end if;
  end if ;
end process;

process(ACC,timeclk,reset,start,stop)
 begin
  if reset='1' then 
 ACC<="000100100000000000000000";
-- hour10<=ACC(23 downto 20);--赋值显示
-- hour1<=ACC(19 downto 16);
 min10<=ACC(15 downto 12);
 min1<=ACC(11 downto 8);
 sec10<=ACC(7 downto 4);
 sec1<=ACC(3 downto 0);
 
  elsif rising_edge(timeclk)and start='1' and stop='0' then 
    if sec1<"1001" then sec1<=sec1+1;
      else 
        sec1<="0000";
        if sec10<"0101" then sec10<=sec10+1;
           else 
           sec10<="0000";
           if min1<"1001" then  min1<=min1+1;
           else
              min1<="0000";
              if min10<"0101" then min10<=min10+1;
              else 
                min10<="0000";--小时的进位要注意
--                if hour10<"0010" then
--                   if hour1<"1001"  then hour1<=hour1+1;
--                    else 
--                      hour1<="0000";
--                      hour10<=hour10+1;
--                   end if;
--                elsif hour10<"0011" then
--                    if hour1<"0011" then hour1<=hour1+1;
--                    else hour1<="0000";hour10<="0000";
--                    end if; 
--                end if;
              end if;
           end if;
     end if;
   end if;
 end if ;
end process;
u:led_disp port map (data,disp);--调显示模块    
end rtl;  
