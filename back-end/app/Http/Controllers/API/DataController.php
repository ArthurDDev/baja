<?php

namespace App\Http\Controllers\API;

use App\Models\Data;
use App\Http\Requests\DataRequest;
use App\Http\Controllers\Controller;
use Illuminate\Http\Request;

class DataController extends Controller
{
    /**
     * Display a listing of the resource.
     */
    public function index()
    {
        $data = Data::all();
        return response()->json([
            'message' => 'OK',
            'data' => $data,
        ], 200);
    }

    /**
     * Store a newly created resource in storage.
     */
    public function store(Request $request)
    {
        $data = Data::create($request->all());
        return response()->json([
            'message' => 'OK',
            'data' => $data,
        ], 201);
    }

    /**
     * Display the specified resource.
     */
    public function show(string $id)
    {
        $data = Data::find($id);
        if(!$data)
            return response()->json([
                'message' => 'Dados nao encontrados',
            ], 404);
        return response()->json([
            'message' => 'OK',
            'data' => $data,
        ], 200);
    }

    /**
     * Update the specified resource in storage.
     */
    public function update(Request $request, string $id)
    {
        $data = Data::find($id);
        if(!$data)
            return response()->json([
                'message' => 'Dados nao encontrados',
                'data' => null,
            ], 404);
        $data->update($request->all());
        return response()->json([
            'message' => 'OK',
            'data' => $data,
        ], 200);
    }

    /**
     * Remove the specified resource from storage.
     */
    public function destroy(string $id)
    {
        $data = Data::find($id);
        if(!$data)
            return response()->json([
                'message' => 'Dados nao encontrados',
                'data' => null,
            ], 404);
        $data->delete();
        return response()->json([
            'message' => 'Dados removidos',
            'data' => $data,
        ], 200);
    }
}
