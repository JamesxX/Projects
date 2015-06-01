include( "shared.lua" )

local matBall = Material( "sprites/sent_ball" )

function ENT:Draw()
	
	local pos = self:GetPos()

	render.SetMaterial( matBall )
	
	local lcolor = render.ComputeLighting( self:GetPos(), Vector( 0, 0, 1 ) )
	local c = self:GetBallColor()
	
	lcolor.x = c.r * ( math.Clamp( lcolor.x, 0, 1 ) + 0.5 ) * 255
	lcolor.y = c.g * ( math.Clamp( lcolor.y, 0, 1 ) + 0.5 ) * 255
	lcolor.z = c.b * ( math.Clamp( lcolor.z, 0, 1 ) + 0.5 ) * 255
	
	render.DrawSprite( pos, self:GetBallSize(), self:GetBallSize(), Color( lcolor.x, lcolor.y, lcolor.z, 255 ) )
	
end