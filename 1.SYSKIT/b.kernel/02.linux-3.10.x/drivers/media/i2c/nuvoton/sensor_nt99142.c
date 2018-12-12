#include <linux/delay.h>
#include <linux/module.h>
#include "nuc970_cap.h"

static struct nuvoton_vin_sensor nt99142;

struct OV_RegValue{
	__u16	uRegAddr;
	__u8	uValue;
};

#define _REG_TABLE_SIZE(nTableName)	sizeof(nTableName)/sizeof(struct OV_RegValue)
/* NT99142, VGA, YUV422 */
static struct OV_RegValue Init_RegValue[] = 
{	
    //{0x3021, 0x60},
#if 1
    /* [Inti] */
    {0x3021, 0x01},	  //Software reset
	{0x3069, 0x01},   // Pad_Config_Pix_Out                            
	{0x306A, 0x02},   // Pclk_Odrv                                     
	{0x3100, 0x03},   // Analog Setting                                
	{0x3101, 0x00},                                                    
	{0x3102, 0x0A},                                                    
	{0x3103, 0x00},                                                    
	{0x3105, 0x03},                                                    
	{0x3106, 0x04},                                                    
	{0x3107, 0x40},                                                    
	{0x3108, 0x00},                                                    
	{0x3109, 0x02},                                                    
	{0x307D, 0x01},                                                    
	{0x310A, 0x05},                                                    
	{0x310C, 0x00},                                                    
	{0x310D, 0x80},                                                    
	{0x3110, 0x33},                                                    
	{0x3111, 0x59},                                                    
	{0x3112, 0x44},                                                    
	{0x3113, 0x66},                                                    
	{0x3114, 0x66},                                                    
	{0x311D, 0x40},                                                    
	{0x3127, 0x01},                                                    
	{0x3129, 0x44},                                                    
	{0x3136, 0x59},                                                    
	{0x313F, 0x02},                                                    
	//{0x30A0, 0x03},   // FPN                                           {0x30A0, 0x00},   // FPN    
	{0x30A1, 0x23},   // FPN_Ctrl_1                                    
	{0x30A2, 0x70},   // FPN_Corr_Again                                
	{0x30A3, 0x01},   // FPN_DPC_Diff                                  
	{0x303E, 0x00},   // Clamp_En                                      
	{0x303F, 0x32},                                                    
	{0x3051, 0x3A},   // ABLC_Ofs_Wgt                                  
	{0x3052, 0x0F},   // OB_Mul                                        
	{0x3055, 0x00},                                                    
	{0x3056, 0x28},   // ABLC_Ofs_Cst                                  
	{0x305F, 0x33},                                                    
	{0x308B, 0x26},   // HG_BLC_Thr_U                                  
	{0x308C, 0x20},   // HG_BLC_Thr_L                                  
	{0x308D, 0x38},   // HG_ABLC_Ofs_Cst                               
	{0x308E, 0x3A},   // HG_ABLC_Ofs_Wgt                               
	{0x308F, 0x0F},   // HG_OB_Mul                                     
	{0x324F, 0x00},   // D light LSC                                   
	{0x3210, 0x0A},                                                    
	{0x3211, 0x0A},                                                    
	{0x3212, 0x0A},                                                    
	{0x3213, 0x0A},                                                    
	{0x3214, 0x0C},                                                    
	{0x3215, 0x0C},                                                    
	{0x3216, 0x0C},                                                    
	{0x3217, 0x0C},                                                    
	{0x3218, 0x0C},                                                    
	{0x3219, 0x0C},                                                    
	{0x321A, 0x0C},                                                    
	{0x321B, 0x0C},                                                    
	{0x321C, 0x0B},                                                    
	{0x321D, 0x0B},                                                    
	{0x321E, 0x0B},                                                    
	{0x321F, 0x0B},                                                    
	{0x3230, 0x03},                                                    
	{0x3231, 0x1D},                                                    
	{0x3232, 0x1D},                                                    
	{0x3233, 0x0F},                                                    
	{0x3234, 0x00},                                                    
	{0x3235, 0x00},                                                    
	{0x3236, 0x00},                                                    
	{0x3237, 0x00},                                                    
	{0x3238, 0x18},                                                    
	{0x3239, 0x18},                                                    
	{0x323A, 0x18},                                                    
	{0x3241, 0x30},                                                    
	{0x3243, 0xC3},                                                    
	{0x3244, 0x00},                                                    
	{0x3245, 0x00},                                                    
	{0x324F, 0x00},                                                    
	{0x3250, 0x2D},   // CA_RG_Top_D                                   
	{0x3251, 0x20},   // CA_RG_Bot_D                                   
	{0x3252, 0x2F},   // CA_BG_Top_D                                   
	{0x3253, 0x23},   // CA_BG_Bot_D                                   
	{0x3254, 0x35},   // CA_RG_Top_F                                   
	{0x3255, 0x25},   // CA_RG_Bot_F                                   
	{0x3256, 0x26},   // CA_BG_Top_F                                   
	{0x3257, 0x1A},   // CA_BG_Bot_F                                   
	{0x3258, 0x44},   // CA_RG_Top_A                                   
	{0x3259, 0x35},   // CA_RG_Bot_A                                   
	{0x325A, 0x24},   // CA_BG_Top_A                                   
	{0x325B, 0x18},   // CA_BG_Bot_A                                   
	{0x325C, 0xA0},                                                    
	{0x3262, 0x00},                                                    
	{0x3268, 0x01},   // CA_Outdoor_Ctrl                               
	{0x3270, 0x00},   // Gamma_Tab_0  // Gamma3                        
	{0x3271, 0x04},   // Gamma_Tab_1                                   
	{0x3272, 0x16},   // Gamma_Tab_2                                   
	{0x3273, 0x2B},   // Gamma_Tab_3                                   
	{0x3274, 0x3F},   // Gamma_Tab_4                                   
	{0x3275, 0x51},   // Gamma_Tab_5                                   
	{0x3276, 0x72},   // Gamma_Tab_6                                   
	{0x3277, 0x8F},   // Gamma_Tab_7                                   
	{0x3278, 0xA7},   // Gamma_Tab_8                                   
	{0x3279, 0xBC},   // Gamma_Tab_9                                   
	{0x327A, 0xDC},   // Gamma_Tab_10                                  
	{0x327B, 0xF0},   // Gamma_Tab_11                                  
	{0x327C, 0xFA},   // Gamma_Tab_12                                  
	{0x327D, 0xFE},   // Gamma_Tab_13                                  
	{0x327E, 0xFF},   // Gamma_Tab_14                                  
	{0x3290, 0x77},                                                    
	{0x3292, 0x73},                                                    
	{0x3297, 0x03},   // AWB_Speed                                     
	{0x32B0, 0x46},   // LA_Win_Ctrl_0                                 
	{0x32B1, 0xBB},   // LA_Win_Ctrl_1                                 
	{0x32B2, 0x14},                                                    
	{0x32B3, 0xA0},                                                    
	{0x32B4, 0x20},                                                    
	{0x32B8, 0x06},                                                    
	{0x32B9, 0x06},                                                    
	{0x32BC, 0x3C},                                                    
	{0x32BD, 0x04},                                                    
	{0x32BE, 0x04},                                                    
	{0x32CB, 0x14},                                                    
	{0x32CC, 0x70},                                                    
	{0x32CD, 0xA0},                                                    
	{0x32F1, 0x05},                                                    
	{0x32F2, 0x80},   // Y_Component                                   
	{0x32FC, 0x00},   // Brt_Ofs                                       
	{0x3302, 0x00},                                                    
	{0x3303, 0x4F},                                                    
	{0x3304, 0x00},                                                    
	{0x3305, 0x9F},                                                    
	{0x3306, 0x00},                                                    
	{0x3307, 0x0F},                                                    
	{0x3308, 0x07},                                                    
	{0x3309, 0xB0},                                                    
	{0x330A, 0x07},                                                    
	{0x330B, 0x04},                                                    
	{0x330C, 0x01},                                                    
	{0x330D, 0x4E},                                                    
	{0x330E, 0x01},                                                    
	{0x330F, 0x06},                                                    
	{0x3310, 0x06},                                                    
	{0x3311, 0xEE},                                                    
	{0x3312, 0x00},                                                    
	{0x3313, 0x0B},                                                    
	{0x3326, 0x14},   // Eext_Mul                                      
	{0x3327, 0x01},   // Eext_Sel                                      
	{0x3332, 0x80},   // Emap_B                                        
	{0x3360, 0x10},                                                    
	{0x3361, 0x1F},                                                    
	{0x3362, 0x26},                                                    
	{0x3363, 0x31},                                                    
	{0x3364, 0x0B},                                                    
	{0x3365, 0x04},   // EmapA_0                                       
	{0x3366, 0x08},   // EmapA_1                                       
	{0x3367, 0x0C},   // EmapA_2                                       
	{0x3368, 0x40},   // Edge_Enhance_0                                
	{0x3369, 0x30},   // Edge_Enhance_1                                
	{0x336B, 0x20},   // Edge_Enhance_2                                
	{0x336D, 0x20},   // NR_DPC_Ratio_0                                
	{0x336E, 0x18},   // NR_DPC_Ratio_1                                
	{0x3370, 0x10},   // NR_DPC_Ratio_2                                
	{0x3371, 0x20},   // NR_Wgt_0                                      
	{0x3372, 0x2F},   // NR_Wgt_1                                      
	{0x3374, 0x3F},   // NR_Wgt_2                                      
	{0x3375, 0x18},   // Edark_Gain_0                                  
	{0x3376, 0x14},   // Edark_Gain_1                                  
	{0x3378, 0x10},   // Edark_Gain_2                                  
	{0x3379, 0x04},   // NR_Comp_Max_0                                 
	{0x337A, 0x06},   // NR_Comp_Max_1                                 
	{0x337C, 0x06},   // NR_Comp_Max_2                                 
	{0x33A0, 0x50},   // AS_EC_Thr_Bri                                 
	{0x33A1, 0x78},   // AS_EC_Thr_Dark                                
	{0x33A2, 0x10},                                                    
	{0x33A3, 0x20},                                                    
	{0x33A4, 0x00},                                                    
	{0x33A5, 0x74},                                                    
	{0x33A7, 0x04},   // Y_Offset                                      
	{0x33A8, 0x00},                                                    
	{0x33A9, 0x00},   // NR_Post_Thr_0                                 
	{0x33AA, 0x02},   // NR_Post_Thr_1                                 
	{0x33AC, 0x02},   // NR_Post_Thr_2                                 
	{0x33AD, 0x02},   // NR_Post_EThr_0                                
	{0x33AE, 0x02},   // NR_Post_EThr_1                                
	{0x33B0, 0x02},   // NR_Post_EThr_2                                
	{0x33B1, 0x00},   // ChromaMap_0                                   
	{0x33B4, 0x48},   // ChromaMap_4                                   
	{0x33B5, 0x44},   // ChromaMap_Y                                   
	{0x33B6, 0xA0},                                                    
	{0x33B9, 0x03},                                                    
	{0x33BD, 0x00},                                                    
	{0x33BE, 0x08},                                                    
	{0x33BF, 0x10},                                                    
	{0x33C0, 0x01},                                                    
	{0x3700, 0x04},                                                    
	{0x3701, 0x0F},                                                    
	{0x3702, 0x1A},                                                    
	{0x3703, 0x32},                                                    
	{0x3704, 0x42},                                                    
	{0x3705, 0x51},                                                    
	{0x3706, 0x6B},                                                    
	{0x3707, 0x81},                                                    
	{0x3708, 0x94},                                                    
	{0x3709, 0xA6},                                                    
	{0x370A, 0xC2},                                                    
	{0x370B, 0xD4},                                                    
	{0x370C, 0xE0},                                                    
	{0x370D, 0xE7},                                                    
	{0x370E, 0xEF},                                                    
	{0x3710, 0x07},                                                    
	{0x371E, 0x02},                                                    
	{0x371F, 0x02},                                                    
	{0x3800, 0x00},                                                    
	{0x3813, 0x07},                                                    
	{0x329F, 0x01}, 
#endif
    //[YUV_640x480_20.00_20.02_FPS_16_48]
	//Set_Device_Format = FORMAT_16_8 
	//SET_Device_Addr = 0x54 
	//MCLK:      16.00MHz 
	//PCLK:      48.00MHz 
	//Size:      640x480 
	//FPS:       20.00~20.02 
	//Line:      1586 
	//Frame:      756 
	//Flicker:   50Hz 
	//file-NT99142_VGA_PCLK_48MHz.dat
	{0x32BB, 0x67}, //50Hz
	{0x32BF, 0x60}, 
	{0x32C0, 0x64}, 
	{0x32C1, 0x64}, 
	{0x32C2, 0x64}, 
	{0x32C3, 0x00}, 
	{0x32C4, 0x30}, 
	{0x32C5, 0x30}, 
	{0x32C6, 0x30}, 
	{0x32D3, 0x00}, 
	{0x32D4, 0x97}, 
	{0x32D5, 0x72}, 
	{0x32D6, 0x00}, 
	{0x32D7, 0x7E}, 
	{0x32D8, 0x6F},  //AE End
	{0x32E0, 0x02},  //Scale Start
	{0x32E1, 0x80}, 
	{0x32E2, 0x01}, 
	{0x32E3, 0xE0}, 
	{0x32E4, 0x00}, 
	{0x32E5, 0x80}, 
	{0x32E6, 0x00}, 
	{0x32E7, 0x80},  //Scale End
	{0x32F0, 0x01},//0x10},  //Output Format
	{0x3200, 0x7E},  //Mode Control
	{0x3201, 0x7D},  //Mode Control
	{0x302A, 0x80},  //PLL Start
	{0x302C, 0x17}, 
	{0x302D, 0x11},  //PLL End
	{0x3022, 0x00},  //Timing Start
	{0x300A, 0x06}, 
	{0x300B, 0x32}, 
	{0x300C, 0x02}, 
	{0x300D, 0xF4},  //Timing End
	{0x320A, 0x38}, 
	{0x3021, 0x02}, 
	{0x3060, 0x01}, 
};

/************  I2C  *****************/
static struct i2c_client *save_client;
static char sensor_inited = 0;

static int sensor_read(u16 reg,u8 *val)
{
	int ret;
	/* We have 16-bit i2c addresses - care for endianess */
	unsigned char data[2] = { reg >> 8, reg & 0xff };

	ret = i2c_master_send(save_client, data, 2);
	if (ret < 2) {
		dev_err(&save_client->dev, "%s: i2c read error, reg: 0x%x\n",
			__func__, reg);
		return ret < 0 ? ret : -EIO;
	}

	ret = i2c_master_recv(save_client, val, 1);
	if (ret < 1) {
		dev_err(&save_client->dev, "%s: i2c read error, reg: 0x%x\n",__func__, reg);
		return ret < 0 ? ret : -EIO;
	}
	return 0;
}

static int sensor_write(u16 reg, u8 val)
{
	int ret;
	unsigned char data[3] = { reg >> 8, reg & 0xff, val };

	ret = i2c_master_send(save_client, data, 3);
	if (ret < 3) {
		dev_err(&save_client->dev, "%s: i2c write error, reg: 0x%x\n",
			__func__, reg);
		return ret < 0 ? ret : -EIO;
	}

	return 0;
}

static int sensor_probe(struct i2c_client *client,const struct i2c_device_id *did)
{
	ENTRY();
	sensor_inited = 1;
	client->flags = I2C_CLIENT_SCCB;
	save_client = client;
	LEAVE();
	return 0;
}
static int sensor_remove(struct i2c_client *client)
{	
	ENTRY();
	LEAVE();
	return 0;
}

static int nt99142_init(struct nuvoton_vin_device* cam)
{
	int err = 0;
	ENTRY();
	LEAVE();		
	return err;
}

static struct nuvoton_vin_sensor nt99142 = {
	.name = "nt99142",
	.init = &nt99142_init,
	.infmtord = (INORD_YUYV | INFMT_YCbCr | INTYPE_CCIR601),
	.polarity = (VSP_LO | HSP_LO | PCLKP_HI),
	.cropstart = ( 0 | 0<<16 ), /*( Vertical | Horizontal<<16 ) */
	.cropcap = {
		.bounds = {
			.left = 0,
			.top = 0,
			.width = 640,
			.height = 480,
		},
		.defrect = {
			.left = 0,
			.top = 0,
			.width = 800,
			.height = 480,
		},
	},
	.pix_format	 = {
		.width = 640,
		.height = 480,
		.pixelformat = V4L2_PIX_FMT_YUYV,
		.priv = 16,
		.colorspace = V4L2_COLORSPACE_JPEG,
	},
};

int nuvoton_vin_probe(struct nuvoton_vin_device* cam)
{
	int i,ret = 0;
	__u8 SensorID[2];
	struct OV_RegValue *psRegValue;	

	ENTRY();	
	nuvoton_vin_attach_sensor(cam, &nt99142);	
		
	// if i2c module isn't loaded at this time
	if(!sensor_inited)
		return -1;
		
	psRegValue=Init_RegValue;
	for(i=0;i<_REG_TABLE_SIZE(Init_RegValue); i++, psRegValue++)
	{		
		printk(".");		
		ret = sensor_write((psRegValue->uRegAddr), (psRegValue->uValue));	
	} 	

	//----------Read sensor id-------------------------------------	        
	sensor_read(0x3000,&SensorID[0]);  /* Chip_Version_H 0x14 */			
	sensor_read(0x3001,&SensorID[1]);  /* Chip_Version_L 0x10 */		
	printk("\nSensor Chip_Version_H = 0x%02x(0x14) Chip_Version_L = 0x%02x(0x10)\n", SensorID[0],SensorID[1]);
	//-------------------------------------------------------------		
	printk("\n");
	if(ret>=0)
		printk("driver i2c initial done\n");
	else
		printk("driver i2c initial fail\n");	
	LEAVE();		
	return ret;	
}

static const struct i2c_device_id sensor_id[] = {{ "nt99142", 0 },};
MODULE_DEVICE_TABLE(i2c, sensor_id);

static struct i2c_driver sensor_i2c_driver = {
	.driver = {
		.name = "nt99142",
				.owner = THIS_MODULE,
						},
	.probe    = sensor_probe,
	.remove   = sensor_remove,	
	.id_table = sensor_id,
};

module_i2c_driver(sensor_i2c_driver);
