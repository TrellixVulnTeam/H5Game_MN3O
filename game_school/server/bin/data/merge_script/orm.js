__human1=require('./orm_slave_human')
__human2=require('./orm_slavetable_human')

__human_slaves=['human'].concat(__slave_of_human)
__human_slave_tables=['humanoperation','mail'].concat(__slavetable_of_human)

__passport_slaves=['passporthuman','passportgold',
'passportvip']

__passport_slave_tables=['passportitems',
'passportloaditems',
'passportnull',
'passportoperation']

__ranklist_names=['ranklist_fightpoint',
'ranklist_arena1v1',
'ranklist_arena3v3',
'ranklist_arena5v5',
'ranklist_level',
'ranklist_achievementscore',
'ranklist_blood',
'ranklist_guild_fightpoint',
'ranklist_gem_fightpoint',
'ranklist_dragon_fightpoint',
'ranklist_ride_fightpoint',
'ranklist_magic_fightpoint',
'ranklist_yzsl'
]

__human_ranklist_names=['ranklist_fightpoint',
'ranklist_arena1v1',
'ranklist_arena3v3',
'ranklist_arena5v5',
'ranklist_level',
'ranklist_achievementscore',
'ranklist_blood',
'ranklist_gem_fightpoint',
'ranklist_dragon_fightpoint',
'ranklist_ride_fightpoint',
'ranklist_magic_fightpoint',
'ranklist_yzsl'
]

__global_tables = ['relation','item','guild','namedhuman','ggameseller','arenaseasonuser','guildtriallandrecord']
__global_salve_tables = ['guildmember']