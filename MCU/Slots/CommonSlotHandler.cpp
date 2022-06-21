#include "CommonSlotHandler.h"
#include "utils.h"

void CommonSlotHandler::parseRespond(Slot& slot, u8* reply) {
	/*получил ссылку на вызвавший слот, чтобы получить доступ к Device:"U1", Section:"RAM"*/
	/*TODO проверить по флагум валиднось данных*/
	/*TODO заполнить данные связанные со слотом, если данные валидны*/
	/*TODO сообщить подписчикам что данные изменились. Это должно привести к:
		- перерисовке отображаемых на экране значений;
		- записи в регистратор;
		- изменение статуса светодиодов*/
	if (slot.Flags & (u16)SlotStateFlags::DATA_VALID) {
		u8 msg_count = reply[2] >> 1;
		swp_copy_u16((u8*)reply[3],
			(u16*)&slot.InputBuf,
			msg_count);
	}
}