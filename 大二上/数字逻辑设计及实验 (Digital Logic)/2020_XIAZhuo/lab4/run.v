//??????????????????
module run (clk,rst,out); 
input clk,rst; 
output [7:0] out; 
reg [7:0] out; 
reg [24:0] count; 
always @ ( posedge clk or negedge rst ) 
	if(!rst) 
	begin 
		count<=16'b0; 
	end 
	else 
	begin 
		count<=count+1; 
	end 

always @ ( posedge clk or negedge rst) 
	if(!rst) 
	begin 
		out<=8'hff; 
	end 
	else 
	begin 
	case ( count[24:21] ) 
		0: out<=8'b1111_1110; 
		1: out<=8'b1111_1101; 
		2: out<=8'b1111_1011; 
        3: out<=8'b1111_0111; 
                4: out<=8'b1110_1111; 
                5: out<=8'b1101_1111; 
                6: out<=8'b1011_1111; 
                7: out<=8'b0111_1111; 
                8: out<=8'b1011_1111; 
                9: out<=8'b1101_1111; 
                10:out<=8'b1110_1111; 
                11:out<=8'b1111_0111; 
                12:out<=8'b1111_1011; 
                13:out<=8'b1111_1101; 
                14:out<=8'b1111_1110; 
                15:out<=8'b1111_1111; 
    endcase 
	end 
endmodule 
