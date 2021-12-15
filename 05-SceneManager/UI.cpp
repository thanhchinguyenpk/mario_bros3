#include "UI.h"
#include "Sprite.h"

void UI::Render(int remainingTime, int the_number_mario_hit_brick, int point_hub, int id_map, int world)
{

	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();


	CSprites::GetInstance()->Get(70010)->Draw(x + 368, y + 645);

	text.Render(x + 405, y + 658, to_string(remainingTime));

	text.Render(x + 190, y + 658, text.FillZeroString(to_string(point_hub), 7));

	text.Render(x + 453, y + 635, to_string(the_number_mario_hit_brick));

	text.Render(x + 140, y + 635, to_string(world));
	text.Render(x + 140, y + 658, to_string(id_map));


	float speed = abs(player->vx);
	int idAni = 12000;
	if (speed < 0.31)
		idAni = 12000;
	else if (speed < 0.38)
		idAni = 12001;
	else if (speed < 0.42)
		idAni = 12002;
	else if (speed < 0.52)
		idAni = 12003;
	else if (speed < 0.58)
		idAni = 12004;
	else if (speed < 0.64)
		idAni = 12005;
	else if (speed <= 0.7)
		idAni = 12006;

	CAnimations::GetInstance()->Get(idAni)->Render(x + 273, y + 635);
	//CSprites::GetInstance()->Get(id_spr)->Draw(x + 273, y + 635);
}
