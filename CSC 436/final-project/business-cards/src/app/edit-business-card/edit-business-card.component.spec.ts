import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { EditBusinessCardComponent } from './edit-business-card.component';

describe('EditBusinessCardComponent', () => {
  let component: EditBusinessCardComponent;
  let fixture: ComponentFixture<EditBusinessCardComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ EditBusinessCardComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(EditBusinessCardComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
