--[[
����
	q �˳�
	c ���������� ����:-N ǰ׺,-s ��ʼid,-e ����id
	gm text ��gm����,����: -s Ӱ����˺ſ�ʼid, -e Ӱ����˺Ž���id
	moveto x y z �ƶ���x,y,z��(��Ҫ������Ѱ·,�ȽϿ�)
	movetorandom x y z dist ��x,y,z���dist����������ƶ�
	caster start ��ʼ���ʩ��
	caster stop  ֹͣ���ʩ��
	ladder_start �����˺ſ�ʼ��¼����
	ladder_clean �����˺Źر�������
	server -i ip -p port �����ӵķ�������Ϊip,port
	close �ر����л�����
	
	GMָ�
	1.���װ��   /random_equip (���ӽ�ɫ�ȼ�����)
	2.��ʼ������ /start_follow (���ѡ��)
	ֹͣ������ /stop_follow
	3.��ʼ���   /robot_startride (���ѡ����)
	ֹͣ���   /robot_stopride
	4.��ʼ���ٻ� /start_summon (���ѡ��)
	ֹͣ���ٻ� /stop_summon
����
	cmd ִ������
	sleep �ȴ�ʱ��(����)
]]--

cmd("server -i 127.0.0.1 -p 8000")

local count = 1
local numperonloop = 10

for i = 0, count do
    local str = "c -N robot -s " .. tostring(i*numperonloop + 1) .. " -e " .. tostring((i+1)*numperonloop)
    cmd(str)

    sleep(5000)
    local str = "gm /gofb 1105 -s " .. tostring(i*numperonloop + 1) .. " -e " .. tostring((i+1)*numperonloop)
    cmd(str)
	sleep(5000)
end

sleep(3000)
cmd("gm /wudi 1")
cmd("caster start")