#include <STC89C5xRC.H>

#include "game_engine.h"
#include "head.h"
#include "input/encoder.h"
#include "oled.h"



#define PAGE_SIZE 3
/* game page */
struct section xdata page[PAGE_SIZE];
struct section data current_section;
/*struct section xdata start_page;
struct section xdata main_game_page;
struct section xdata attribute;	*/

struct option data current_line;
/* player property */
struct entity data player;

static bit btn_flag = 0;
static unsigned char single_click = 0;
static bit double_click = 0;
static unsigned char t1_int_count = 0;

void Game_Init(void)
{
    /* ��ʼ��ʵ������ */
    player = MakeEntity(10,5,100);
    /* ��ʼ����ҳ */
    page[0].line1 = MakeOption(1, "", NORMAL, CENTER);
    page[0].line2 = MakeOption(2, "Start Game", NORMAL, CENTER);
    page[0].line3 = MakeOption(3, "Continue Game", NORMAL, CENTER);
    page[0].line4 = MakeOption(4, "Help", INVERT, CENTER);

    /*start_page = MakeSection(line1,line2,line3,line4);
    start_page.name = "start";*/
    page[0].name ="start";
    page[0].line2.next = "main";


    /* ��Ϸ������ */
    page[1].line1 = MakeOption(1, "Attribute", INVERT, CENTER);
    page[1].line2 = MakeOption(2, "Backpack", NORMAL, CENTER);
    page[1].line3 = MakeOption(3, "Cave", NORMAL, CENTER);
    page[1].line4 = MakeOption(4, "Discover", NORMAL, CENTER);
    //main_game_page = MakeSection(line1,line2,line3,line4);
    page[1].name  ="main";
    page[1].line1.next = "attribute";

    /* ���� */
    page[2].line1 = MakeOption(1, "Damage", NORMAL, LEFT);
    page[2].line2 = MakeOption(2, "Defense", NORMAL, LEFT);
    page[2].line3 = MakeOption(3, "Health", NORMAL, LEFT);
    page[2].line4 = MakeOption(4, "-----", NORMAL, LEFT);
    //attribute = MakeSection(line1,line2,line3,line4);
    page[2].name = "attribute";

    /* Backpack */
    /* Cave */
    /* Discover */

    /* ҳ��ָ�� */
    current_section=page[0];
}

void Game_Start()
{
    Show_Game_Menu(current_section);
}

struct section entrySection(struct option line)
{
    unsigned char *name, i;
    name = line.next;
    for(i=0; i<PAGE_SIZE; i++)
    {
        if(name == page[i].name)
        {
            Hide_Game_Menu(current_section);
            current_section=page[i];
            Show_Game_Menu(current_section);
        }
    }

}

bit CheckIfDoubleClick()
{
    //XICON &= ~(1<<6);
    //while(t1_int_count<50);
    //TR1 = 0;
    //XICON |= (1<<6);
    //TR1=1;
    while(1)
    {
        if(TF1)
        {
            TF1=0;
            t1_int_count++;
        }

    }
    while(t1_int_count<100)
    {

        if(btn_flag)
        {
            t1_int_count=0;
            return 1;
        }
    }
    return 0;
}

void Game_Loop()
{
    unsigned char ec11_res;
    unsigned char which_line_selected;
    unsigned char line_number = 0;

    //get encoder dat
    ec11_res = Encoder_Key_Scan();

//pre option

    /*current_line = findWitchIsSelected(current_section);
    which_line_selected = current_line.which;
    switch(which_line_selected)
    {
    	case 1:line_number=0;break;
    	case 2:line_number=2;break;
    	case 3:line_number=4;break;
    	case 4:line_number=6;break;
    	default:break;
    }*/
    if(ec11_res=='L' || ec11_res=='R')
    {
        if(current_section.line1.isSelected==(unsigned char)-1)
        {
            which_line_selected=current_section.line1.which;
            current_section.line1.isSelected=(unsigned char)1;
            OLEDPrint(0,0,current_section.line1.text,current_section.line1.alignment,current_section.line1.isSelected);
        }
        if(current_section.line2.isSelected==(unsigned char)-1)
        {
            which_line_selected=current_section.line2.which;
            current_section.line2.isSelected=(unsigned char)1;
            OLEDPrint(2,0,current_section.line2.text,current_section.line2.alignment,current_section.line2.isSelected);
        }
        if(current_section.line3.isSelected==(unsigned char)-1)
        {
            which_line_selected=current_section.line3.which;
            current_section.line3.isSelected=(unsigned char)1;
            OLEDPrint(4,0,current_section.line3.text,current_section.line3.alignment,current_section.line3.isSelected);
        }
        if(current_section.line4.isSelected==(unsigned char)-1)
        {
            which_line_selected=current_section.line4.which;
            current_section.line4.isSelected=(unsigned char)1;
            OLEDPrint(6,0,current_section.line4.text,current_section.line4.alignment,current_section.line4.isSelected);
        }
    }

    if(ec11_res=='L')
    {
        which_line_selected = clacNextOption(current_section, which_line_selected, ec11_res);
    }
    else if(ec11_res=='R')
    {
        which_line_selected = clacNextOption(current_section, which_line_selected, ec11_res);
    }

    if(ec11_res=='L' || ec11_res=='R')
    {
        switch(which_line_selected)
        {
        case (unsigned char)1:
        {
            current_section.line1.isSelected=(unsigned char)-1;
            //OLEDPrint(0,0,current_section.line1.text, current_section.line1.alignment,CLEAR);
            OLEDPrint(0,0,current_section.line1.text, current_section.line1.alignment,current_section.line1.isSelected);
            break;
        }
        case (unsigned char)2:
        {
            current_section.line2.isSelected=(unsigned char)-1;
            //OLEDPrint(2,0,current_section.line2.text, current_section.line2.alignment,CLEAR);
            OLEDPrint(2,0,current_section.line2.text, current_section.line2.alignment,current_section.line2.isSelected);
            break;
        }
        case (unsigned char)3:
        {
            current_section.line3.isSelected=(unsigned char)-1;
            //OLEDPrint(4,0,current_section.line3.text, current_section.line3.alignment,CLEAR);
            OLEDPrint(4,0,current_section.line3.text, current_section.line3.alignment,current_section.line3.isSelected);
            break;
        }
        case (unsigned char)4:
        {
            current_section.line4.isSelected=(unsigned char)-1;
            //OLEDPrint(6,0,current_section.line4.text, current_section.line4.alignment,CLEAR);
            OLEDPrint(6,0,current_section.line4.text, current_section.line4.alignment,current_section.line4.isSelected);
            break;
        }
        default:
            break;
        }
    }

    if(btn_flag)
    {
        btn_flag=0;
        double_click = CheckIfDoubleClick();
    }

    if(double_click)
    {
        OLEDPrint(0,0,"dclick",0,NORMAL);
        OLEDPrint(0,0,"dclick",0,CLEAR);
        double_click=0;
    }
    //enter option
    if(btn_flag)
    {
        struct option line1;
        btn_flag=0;
        line1=findWitchIsSelected(current_section);
        entrySection(line1);
    }


}
// ��ʱ��1�жϷ������
void timer1_Routine(void) interrupt INT_TIMER1
{
    TL1 = 0x00;
    TH1 = 0x28;
}

// ���������½����жϷ����ж��Ƿ�Ϊ˫��������Ϊ������
void int3_Routine(void) interrupt INT_INT3
{
    btn_flag=1;
    TL1 = 0x00;
    TH1 = 0x28;
    TF1 = 0;
    TR1 = 1;
}
