#include "Rigidbody.h"
#include "Transform.h"

void Rigidbody::AddForce(const Vector2& velocity)
{
	vel += velocity;
}

void Rigidbody::Update()
{
	auto& object1 = gameObject();
	for (int hit_layer : hit_layers)
	{
		auto& layer = GameObject::FindGameObjectsWithLayer(hit_layer);
		for (auto& wobject : layer)
			if (auto object2 = wobject.lock())
				if (object2 && !object2->IsDestroyed() && object1 != object2)
				{
					auto collider1 = object1->GetComponent<Collider>();
					auto collider2 = object2->GetComponent<Collider>();
					if (collider1 && collider2)
					{
						CollisionResult result = collider1->Collide(*collider2);
						if (result.hit)
						{
							{
								if (!collider1->isTrigger && !collider2->isTrigger)
									collider1->Apply(result);
								auto event1 = object1->GetComponent<CollisionEvent>();
								if (event1)
									if (collider1->isTrigger || collider2->isTrigger)
										event1->OnTriggerEnter(*object2);
									else
										event1->OnCollisionEnter(*object2);
							}
							//if (!object2->HasComponent<Rigidbody>())
							{
								if (!collider1->isTrigger && !collider2->isTrigger)
									collider2->Apply(result);
								auto event2 = object2->GetComponent<CollisionEvent>();
								if (event2)
									if (collider1->isTrigger || collider2->isTrigger)
										event2->OnTriggerEnter(*object1);
									else
										event2->OnCollisionEnter(*object1);
							}
						}
					}
				}
	}

	gameObject()->transform()->position += vel;
}