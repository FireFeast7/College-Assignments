import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedHashMap;

public class passone {
	int lc=0;
	int libtab_ptr=0,pooltab_ptr=0;
	int symIndex=0,litIndex=0;
	LinkedHashMap<String, Tablerow> SYMTAB;
	ArrayList<Tablerow> LITTAB;
	ArrayList<Integer> POOLTAB;
	private BufferedReader br;

	public passone()
	{
		SYMTAB =new LinkedHashMap<>();
		LITTAB=new ArrayList<>();
		POOLTAB=new ArrayList<>();
		lc=0;
		POOLTAB.add(0);
	}
	public static void main(String[] args) {
		passone one=new passone();
		try
		{
			one.parseFile();
		}
		catch (Exception e) {
			System.out.println("Error: "+e);
		}
	}
	public void parseFile() throws Exception
	{String prev="";
		String line,code;
		br = new BufferedReader(new FileReader("input.asm"));
		BufferedWriter bw=new BufferedWriter(new FileWriter("IC.txt"));
		OPtable lookup=new OPtable();
		while((line=br.readLine())!=null)
		{
			
			String parts[]=line.split("\\s+");
			if(!parts[0].isEmpty()) 
			{
				if(SYMTAB.containsKey(parts[0]))
					SYMTAB.put(parts[0], new Tablerow(parts[0], lc, SYMTAB.get(parts[0]).getIndex()));
				else
					SYMTAB.put(parts[0],new Tablerow(parts[0], lc, ++symIndex));
			}

			if(parts[1].equals("LTORG"))
			{
				int ptr=POOLTAB.get(pooltab_ptr);
				for(int j=ptr;j<libtab_ptr;j++)
				{
					lc++;
					LITTAB.set(j, new Tablerow(LITTAB.get(j).getSymbol(),lc));
					code="(DL,01)\t(C,"+LITTAB.get(j).symbol+")";
					bw.write(code+"\n");
				}
				pooltab_ptr++;
				POOLTAB.add(libtab_ptr);
			}
			if(parts[1].equals("START"))
			{
				lc=expr(parts[2]);
				code="(AD,01)\t(C,"+lc+")";
				bw.write(code+"\n");
				prev="START";
			}
			else if(parts[1].equals("ORIGIN"))
			{
				lc=expr(parts[2]);
				String splits[]=parts[2].split("\\+"); 
				code="(AD,03)\t(S,"+SYMTAB.get(splits[0]).getIndex()+")+"+Integer.parseInt(splits[1]);
				bw.write(code+"\n");
			}

			//Now for EQU
			if(parts[1].equals("EQU"))
			{
				int loc=expr(parts[2]);
			
				if(parts[2].contains("+"))
				{
					String splits[]=parts[2].split("\\+");
					code="(AD,04)\t(S,"+SYMTAB.get(splits[0]).getIndex()+")+"+Integer.parseInt(splits[1]);

				}
				else if(parts[2].contains("-"))
				{
					String splits[]=parts[2].split("\\-");
					code="(AD,04)\t(S,"+SYMTAB.get(splits[0]).getIndex()+")-"+Integer.parseInt(splits[1]);
				}
				else
				{
					code="(AD,04)\t(C,"+Integer.parseInt(parts[2]+")");
				}
				bw.write(code+"\n");
				if(SYMTAB.containsKey(parts[0]))
					SYMTAB.put(parts[0], new Tablerow(parts[0],loc,SYMTAB.get(parts[0]).getIndex())) ;
				else
					SYMTAB.put(parts[0], new Tablerow(parts[0],loc,++symIndex));	 
			}

			if(parts[1].equals("DC"))
			{
				lc++;
				int constant=Integer.parseInt(parts[2].replace("'",""));
				code="(DL,01)\t(C,"+constant+")";
				bw.write(code+"\n");
			}
			else if(parts[1].equals("DS"))
			{
				
				int size=Integer.parseInt(parts[2].replace("'", ""));

				code="(DL,02)\t(C,"+size+")";
				bw.write(code+"\n");
                lc=lc+size;
				prev="";
			}
			if(lookup.getTypes(parts[1]).equals("IS"))
			{
				code="(IS,0"+lookup.getCode(parts[1])+")\t";
				int j=2;
				String code2="";
				while(j<parts.length)
				{
					parts[j]=parts[j].replace(",", "");
					if(lookup.getTypes(parts[j]).equals("RG"))
					{
						code2+=lookup.getCode(parts[j])+"\t";
					}
					else
					{
						if(parts[j].contains("="))
						{
							parts[j]=parts[j].replace("=", "").replace("'", "");
							LITTAB.add(new Tablerow(parts[j], -1,++litIndex));
							libtab_ptr++;
							code2+="(L,"+(litIndex)+")";
						}
						else if(SYMTAB.containsKey(parts[j]))
						{
							int ind=SYMTAB.get(parts[j]).getIndex();
							code2+= "(S,0"+ind+")"; 
						}
						else
						{
							SYMTAB.put(parts[j], new Tablerow(parts[j],-1,++symIndex));
							int ind=SYMTAB.get(parts[j]).getIndex();
							code2+= "(S,0"+ind+")";
						}
					}
					j++;
				}
				lc++;
				code=code+code2;
				bw.write(code+"\n");
			}
			
			if(parts[1].equals("END"))
			{
				int ptr=POOLTAB.get(pooltab_ptr);
				for(int j=ptr;j<libtab_ptr;j++)
				{
					lc++;
					LITTAB.set(j, new Tablerow(LITTAB.get(j).getSymbol(),lc));
					code="(DL,01)\t(C,"+LITTAB.get(j).symbol+")";
					bw.write(code+"\n");
				}
				pooltab_ptr++;
				POOLTAB.add(libtab_ptr);
				code="(AD,02)";
				bw.write(code+"\n");
			}

		}
		bw.close();
		printSYMTAB();
		//Printing Literal table
		PrintLITTAB();
		printPOOLTAB();
	}
	void PrintLITTAB() throws IOException
	{
		BufferedWriter bw=new BufferedWriter(new FileWriter("LITTAB.txt"));
		System.out.println("\nLiteral Table\n");
		//Processing LITTAB
		for(int i=0;i<LITTAB.size();i++)
		{
			Tablerow row=LITTAB.get(i);
			System.out.println(i+"\t"+row.getSymbol()+"\t"+row.getAddress());
			bw.write((i+1)+"\t"+row.getSymbol()+"\t"+row.getAddress()+"\n");
		}
		bw.close();
	}
	void printPOOLTAB() throws IOException
	{
		BufferedWriter bw=new BufferedWriter(new FileWriter("POOLTAB.txt"));
		System.out.println("\nPOOLTAB");
		System.out.println("Index\t#first");
		for (int i = 0; i < POOLTAB.size(); i++) {
			System.out.println(i+"\t"+POOLTAB.get(i));
			bw.write((i+1)+"\t"+POOLTAB.get(i)+"\n");
		}
		bw.close();
	}
	void printSYMTAB() throws IOException
	{
		BufferedWriter bw=new BufferedWriter(new FileWriter("SYMTAB.txt"));
		
		java.util.Iterator<String> iterator = SYMTAB.keySet().iterator();
		System.out.println("SYMBOL TABLE");
		while (iterator.hasNext()) {
			String key = iterator.next().toString();
			Tablerow value = SYMTAB.get(key);

			System.out.println(value.getIndex()+"\t" + value.getSymbol()+"\t"+value.getAddress());
			bw.write(value.getIndex()+"\t" + value.getSymbol()+"\t"+value.getAddress()+"\n");
		}
		bw.close();
	}
	public int expr(String str)
	{
		int temp=0;
		if(str.contains("+"))
		{
			String splits[]=str.split("\\+");
			temp=SYMTAB.get(splits[0]).getAddress()+Integer.parseInt(splits[1]);
		}
		else if(str.contains("-"))
		{
			String splits[]=str.split("\\-");
			temp=SYMTAB.get(splits[0]).getAddress()-(Integer.parseInt(splits[1]));
		}
		else
		{
			temp=Integer.parseInt(str);
		}
		return temp;
	}
}