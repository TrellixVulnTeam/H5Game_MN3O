cmd('server -i 10.68.43.10 -p 8000')
--cmd('server -i 10.64.72.97 -p 8000')

cmd('c -N robot -s 1 -e 24')
sleep(2000)

cmd('gm /fixmagics')
cmd('gm /levelup 50')
cmd('gm /switch_dungeon 1201')
cmd('gm /create_team 1 3')

sleep(5000)
cmd('ladder_start')

    