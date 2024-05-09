#include "kalman.h"
#include "math.h"
#include "mdefine.h"

/*
  ״̬���Ƶķ�����������ķ��ģ��Ԥ��ֵ�ķ����Ԥ��ֵ�����ʵֵ��ƫ���ƽ��
*/

/* 
  ��ʼ���������˲���,Q R ��ֵ��Ҳ���ܻ��ܵ������Ĳ���Ӱ�죬R ����ֵԽ������Խ����³����Խ��
  R Ϊ��ֵʱ����ʾ����ֵ���ڲ���ֵ��R Ϊ����ʱ����ʾ����ֵ�Ȳ���ֵС���� SOC ���ʱ R ����ֵ����
  SOC ʵ��ʱ R �ø�ֵ
*/

/*
  �ڿ������˲��У�ϵͳ�����Ͳ��������Խ���������Ӱ�졣ϵͳ������ָ����ʵϵͳ�д��ڵ��޷�Ԥ֪��������
  ������������ָ�ڴ��������������в�����������ϵͳ�����Ĵ�С��Ӱ�쵽�������˲�����ϵͳ״̬��Ԥ�⡣
  ���ϵͳ�����ϴ󣬿������˲�����������������ֵ������״̬���ƣ��������˶�ϵͳ״̬������֪ʶ��
  �����ᵼ�¹��ƽ�����ӽӽ�����ֵ����Ҳ�����ӹ��������������Ĵ�С��Ӱ�쵽�������˲����Բ���ֵ��Ȩ�ط��䡣
  ������������ϴ󣬿������˲������������ϵͳģ�͵�Ԥ�⣬�����Բ���ֵ�������ᵼ�¹��ƽ������ƽ����
  ��Ҳ���ӳٶ�ϵͳ״̬�仯����Ӧ����ˣ�ϵͳ�����Ͳ�����������Կ������˲����Ĺ��ƽ������Ӱ�죬������С
  ���������ᵼ�¹��ƽ���Ĳ�׼ȷ�ԡ�
*/

/*
  ����ֵΪ0.01��0.1��1֮������������
  ����ֵΪ0.01��ʾ���ݵ���ɢ�̶Ƚ�С�����ݵ���Լ����ھ�ֵ�����������Խ�С��
  ����ֵΪ0.1��ʾ���ݵ���ɢ�̶����У����ݵ��ھ�ֵ�������ֽ�Ϊ���ȵķֲ���
  ����ֵΪ1��ʾ���ݵ���ɢ�̶Ƚϴ����ݵ���Է�ɢ�������Խϴ�
*/

/* ���ڽ������������� */
KalmanFilter kf_current;

/* ���ڽ�� SOC ϵͳ��� */
KalmanFilter kf_soc;

void kalman_filter_init(KalmanFilter *kf, float X0, float P0, float R)
{
  kf -> X = X0;    // ״̬���ƣ�ѭ������
  kf -> P = P0;    // ״̬���Ƶķ��ѭ������
  kf -> A = 1;     // ״̬ת�ƾ���ģ�;���
  kf -> H = 1;     // �۲����ģ�;���
  kf -> Q = 0.01;  // ϵͳ����Э������飬���ݲ����е�ֵ���� / ���ݼ���������
  kf -> R = R;     // ��������Э������飬���ݲ����е�ֵ���� / ���ݼ���������
}

// �������˲���Ԥ�ⲽ��
void kalman_filter_predict(KalmanFilter *kf)
{
  // ״̬Ԥ��
  kf -> X = kf -> A * kf -> X;
  
  // ����Ԥ��
  kf -> P = kf -> A * kf -> P * kf -> A + kf -> Q;
}

// �������˲������²���
void kalman_filter_update(KalmanFilter *kf, float z)
{
  // ���㿨��������
  float K = kf -> P * kf -> H / (kf -> H * kf -> P * kf -> H + kf -> R);
  
  // ����״̬����
  kf -> X = kf -> X + K * (z - kf -> H * kf -> X);
  
  // ���·������
  kf -> P = (1 - K * kf -> H) * kf -> P;
}

/* ����ͻ����������ú��ʵ�״̬������ʹ������ٵ����� */
void kalman_filter_x_update(KalmanFilter *kf, float x)
{
  kf -> X = x;
}

// ����ѭ���У�ѭ������
float KalmanFliter(KalmanFilter *kf, float Measurement_Value)
{
  float Estimate_Value;
  kalman_filter_predict(kf);                               // Ԥ�ⲽ��
  kalman_filter_update(kf, Measurement_Value);             // ���²���
  Estimate_Value = kf -> X;                                // �õ�����ֵ
  return Estimate_Value;
}

/* �����Ŀ������˲���ʼ�� */
void CurrentKalmanFliterInit(void)
{
  kalman_filter_init(&kf_current, 0, 1, 10);
}

/* Soc �Ŀ������˲���ʼ�� */
void SocKalmanFliterInit(float R)
{
  kalman_filter_init(&kf_soc, 0, 1, R);
}

/* �����������˲� */ 
float CurrentKalmanFliter(float Measurement_Value)
{
  float Current_Estimate = KalmanFliter(&kf_current, Measurement_Value);
  // printf("\r\nCurrent_Measurement:%f,Current_Estimate:%f\r\n",Measurement_Value, Current_Estimate);
  return Current_Estimate;
}

/* Soc �������˲� */ 
float SocKalmanFliter(float Measurement_Value)
{
  float Soc_Estimate = KalmanFliter(&kf_soc, Measurement_Value);
  // printf("\r\nSoc_Measurement:%f,Soc_Estimate:%f\r\n",Measurement_Value, Soc_Estimate);
  return Soc_Estimate;
}

/*
 ����ֵ����С
 y = -4E-07x3 + 1E-05x2 - 0.002x - 0.0022
 R2 = 0.9996

 y = [0, 0.09],  soc ������Χ��[-1��-32]
*/
float GetPositiveRvalue(uint8_t x)
{
#if 0
  float y0 = 4.0 * pow(10, -7) * pow(x, 3);
  float y1 = 1.0 * pow(10, -5) * pow(x, 2);
  float y2 = 0.002 * x;
  float y = y0 + y1 + y2 - 0.0021;
  return y;
  
#else
  union
  {
    float rf;
    uint32_t r32;
  }Rn;
  
  uint32_t *pointer = (uint32_t*)WRITE_KALMAN_ADDR;
  Rn.r32 = pointer[x];
  return Rn.rf;
#endif
  
}

/*
 ����ֵ����С
 y = 8E-08x3 - 2E-05x2 + 0.002x + 0.0023 
 R2 = 0.999],  soc ������Χ��[-1��80]

 y = [-0.06, 0]
*/
float GetNegativeRvalue(uint8_t x)
{
#if 0
  float y0 = -8 * pow(10,-8) * pow(x,3);
  float y1 =  2 * pow(10,-5) * pow(x,2);
  float y2 = -0.002 * x;
  float y = y0 + y1 + y2 - 0.0023;
  return y;
  
#else
  union
  {
    float rf;
    uint32_t r32;
  }Rn;
  
  uint32_t *pointer = (uint32_t*)WRITE_KALMAN_ADDR;
  Rn.r32 = pointer[x + 50];
  return Rn.rf;
#endif
  
}

// Kalman ����
void Kalman_Test(void)
{
	uint8_t estimate[101] = {0};
	uint8_t measure = 0;
	
  SocKalmanFliterInit(1.0);

  for(measure = 1; measure <= 100; measure ++)
  {
    estimate[measure] = SocKalmanFliter(measure);
  }
  
  if(estimate[100] == 0)return;
}















