
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = 'END LIMF LIMI NUM SEP STARTFrase : LIMI Elementos LIMFElementos : Elementos SEP ElementoElementos : ElementoElementos : emptyElemento : NUMElemento : STARTElemento : ENDempty :'
    
_lr_action_items = {'LIMI':([0,],[2,]),'$end':([1,9,],[0,-1,]),'NUM':([2,10,],[6,6,]),'START':([2,10,],[7,7,]),'END':([2,10,],[8,8,]),'LIMF':([2,3,4,5,6,7,8,11,],[-8,9,-3,-4,-5,-6,-7,-2,]),'SEP':([2,3,4,5,6,7,8,11,],[-8,10,-3,-4,-5,-6,-7,-2,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'Frase':([0,],[1,]),'Elementos':([2,],[3,]),'Elemento':([2,10,],[4,11,]),'empty':([2,],[5,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> Frase","S'",1,None,None,None),
  ('Frase -> LIMI Elementos LIMF','Frase',3,'p_Frase','ex1_2.py',22),
  ('Elementos -> Elementos SEP Elemento','Elementos',3,'p_Elementos','ex1_2.py',25),
  ('Elementos -> Elemento','Elementos',1,'p_Elementos_simples','ex1_2.py',28),
  ('Elementos -> empty','Elementos',1,'p_Elementos_vazio','ex1_2.py',31),
  ('Elemento -> NUM','Elemento',1,'p_Elemento','ex1_2.py',34),
  ('Elemento -> START','Elemento',1,'p_Elemento_limiteI','ex1_2.py',38),
  ('Elemento -> END','Elemento',1,'p_Elemento_limiteF','ex1_2.py',41),
  ('empty -> <empty>','empty',0,'p_empty','ex1_2.py',50),
]
