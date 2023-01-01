#include "CMockCanvas.h"

void CMockCanvas::DrawLine(const CPoint& firstPoint, const CPoint& secondPoint, uint32_t outlineColor)
{
	m_notifications.push_back(Notification::DrawLine);
}

void CMockCanvas::DrawPolygon(const std::vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor)
{
	m_notifications.push_back(Notification::DrawPolygon);
}

void CMockCanvas::DrawCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
	m_notifications.push_back(Notification::DrawCircle);
}

std::vector<CMockCanvas::Notification> CMockCanvas::GetNotifications() const
{
	return m_notifications;
}
