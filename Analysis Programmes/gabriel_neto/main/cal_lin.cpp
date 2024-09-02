#include "data_colector.cpp"

int main(){
    
    data_colector alfa("cal_lin.txt");
    vector<double> x = alfa.get_a_certain_col(2);
    vector<double> ex;
    vector<double> y = alfa.get_a_certain_col(1);
    vector<double> ey;
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){
        
        ex.push_back(1);
        ey.push_back(0.01);
    }

    double* x_ptr = &x[0];
    double* ex_ptr = &ex[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_ptr, ey_ptr);
    TF1* f = new TF1("f", "[0] * x + [1]");
    TPaveText* pt = new TPaveText(450, 4.5, 600, 5.5, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Channels");
    g->GetXaxis()->SetLimits(400, 750);
    g->GetXaxis()->SetNdivisions(-514);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Energy (pulser units)");
    g->GetYaxis()->SetRangeUser(3, 5.60);
    g->GetYaxis()->SetNdivisions(-413);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    pt->AddText(Form("y = ax + b"));
    pt->AddText(Form("a = %.5f %c %.5f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.3f %c %.3f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.1f", f->GetChisquare()));
    pt->Draw();

    C->Update();
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete pt;
    delete A;

    return 0;
}